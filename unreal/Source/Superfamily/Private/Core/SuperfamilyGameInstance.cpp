// Copyright (c) 2024 Superfamily B.V. All Rights Reserved.

#include "Core/SuperfamilyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SaveGame.h"

// Forward declare save game class (will be implemented later)
UCLASS()
class USuperFamilySaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(SaveGame)
	FString FamilyAccountID;

	UPROPERTY(SaveGame)
	TArray<FChildProfile> ChildProfiles;

	UPROPERTY(SaveGame)
	FDateTime LastModified;

	UPROPERTY(SaveGame)
	int32 SaveVersion = 1;
};

const FString USuperfamilyGameInstance::SaveSlotName = TEXT("SuperfamilySave");

USuperfamilyGameInstance::USuperfamilyGameInstance()
{
	AudioCulture = TEXT("nl");
}

void USuperfamilyGameInstance::Init()
{
	Super::Init();

	// Try to load existing save
	LoadGame();

	UE_LOG(LogTemp, Log, TEXT("Superfamily GameInstance initialized"));
}

void USuperfamilyGameInstance::Shutdown()
{
	// Auto-save on shutdown
	SaveGame();

	Super::Shutdown();
}

FChildProfile USuperfamilyGameInstance::GetActiveProfile() const
{
	if (CurrentSaveGame)
	{
		for (const FChildProfile& Profile : CurrentSaveGame->ChildProfiles)
		{
			if (Profile.ChildID == ActiveChildID)
			{
				return Profile;
			}
		}
	}
	return FChildProfile();
}

bool USuperfamilyGameInstance::SetActiveProfile(const FString& ChildID)
{
	if (CurrentSaveGame)
	{
		for (const FChildProfile& Profile : CurrentSaveGame->ChildProfiles)
		{
			if (Profile.ChildID == ChildID)
			{
				ActiveChildID = ChildID;
				return true;
			}
		}
	}
	return false;
}

TArray<FChildProfile> USuperfamilyGameInstance::GetAllProfiles() const
{
	if (CurrentSaveGame)
	{
		return CurrentSaveGame->ChildProfiles;
	}
	return TArray<FChildProfile>();
}

bool USuperfamilyGameInstance::CreateProfile(const FString& DisplayName, int32 AgeGroup)
{
	if (!CurrentSaveGame)
	{
		CurrentSaveGame = Cast<USuperFamilySaveGame>(UGameplayStatics::CreateSaveGameObject(USuperFamilySaveGame::StaticClass()));
	}

	FChildProfile NewProfile;
	NewProfile.ChildID = FGuid::NewGuid().ToString();
	NewProfile.DisplayName = DisplayName;
	NewProfile.AgeGroup = FMath::Clamp(AgeGroup, 1, 4);
	NewProfile.TotalXP = 0;
	NewProfile.Coins = 0;
	NewProfile.CurrentStreak = 0;
	NewProfile.LastPlayedDate = FDateTime::Now();

	CurrentSaveGame->ChildProfiles.Add(NewProfile);

	// Set as active if first profile
	if (CurrentSaveGame->ChildProfiles.Num() == 1)
	{
		ActiveChildID = NewProfile.ChildID;
	}

	return SaveGame();
}

bool USuperfamilyGameInstance::SaveGame()
{
	if (CurrentSaveGame)
	{
		CurrentSaveGame->LastModified = FDateTime::UtcNow();
		return UGameplayStatics::SaveGameToSlot(CurrentSaveGame, SaveSlotName, 0);
	}
	return false;
}

bool USuperfamilyGameInstance::LoadGame()
{
	if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0))
	{
		CurrentSaveGame = Cast<USuperFamilySaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
		if (CurrentSaveGame && CurrentSaveGame->ChildProfiles.Num() > 0)
		{
			ActiveChildID = CurrentSaveGame->ChildProfiles[0].ChildID;
		}
		return CurrentSaveGame != nullptr;
	}

	// Create new save game
	CurrentSaveGame = Cast<USuperFamilySaveGame>(UGameplayStatics::CreateSaveGameObject(USuperFamilySaveGame::StaticClass()));
	return true;
}

bool USuperfamilyGameInstance::DoesSaveExist() const
{
	return UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0);
}

void USuperfamilyGameInstance::RecordLevelCompletion(int32 WorldID, int32 LevelID, int32 Stars, int32 Score, int32 Coins)
{
	if (!CurrentSaveGame)
	{
		return;
	}

	FChildProfile* ActiveProfile = nullptr;
	for (FChildProfile& Profile : CurrentSaveGame->ChildProfiles)
	{
		if (Profile.ChildID == ActiveChildID)
		{
			ActiveProfile = &Profile;
			break;
		}
	}

	if (!ActiveProfile)
	{
		return;
	}

	FString LevelKey = GetLevelKey(WorldID, LevelID);
	FLevelProgress& Progress = ActiveProfile->LevelProgress.FindOrAdd(LevelKey);

	Progress.bCompleted = true;
	Progress.StarsEarned = FMath::Max(Progress.StarsEarned, Stars);
	Progress.HighScore = FMath::Max(Progress.HighScore, Score);
	Progress.CoinsCollected = FMath::Max(Progress.CoinsCollected, Coins);

	// Add coins to total
	ActiveProfile->Coins += Coins;

	SaveGame();
}

FLevelProgress USuperfamilyGameInstance::GetLevelProgress(int32 WorldID, int32 LevelID) const
{
	if (!CurrentSaveGame)
	{
		return FLevelProgress();
	}

	for (const FChildProfile& Profile : CurrentSaveGame->ChildProfiles)
	{
		if (Profile.ChildID == ActiveChildID)
		{
			FString LevelKey = GetLevelKey(WorldID, LevelID);
			if (const FLevelProgress* Progress = Profile.LevelProgress.Find(LevelKey))
			{
				return *Progress;
			}
			break;
		}
	}

	return FLevelProgress();
}

bool USuperfamilyGameInstance::IsLevelUnlocked(int32 WorldID, int32 LevelID) const
{
	// First level of first world is always unlocked
	if (WorldID == 1 && LevelID == 1)
	{
		return true;
	}

	// Check if previous level is completed
	int32 PrevWorld = WorldID;
	int32 PrevLevel = LevelID - 1;

	if (PrevLevel < 1)
	{
		// First level of world - check boss of previous world
		PrevWorld = WorldID - 1;
		PrevLevel = 10; // Boss level
	}

	FLevelProgress PrevProgress = GetLevelProgress(PrevWorld, PrevLevel);
	return PrevProgress.bCompleted;
}

void USuperfamilyGameInstance::AddXP(int32 Amount)
{
	if (!CurrentSaveGame || Amount <= 0)
	{
		return;
	}

	for (FChildProfile& Profile : CurrentSaveGame->ChildProfiles)
	{
		if (Profile.ChildID == ActiveChildID)
		{
			Profile.TotalXP += Amount;
			SaveGame();
			return;
		}
	}
}

void USuperfamilyGameInstance::AddCoins(int32 Amount)
{
	if (!CurrentSaveGame || Amount <= 0)
	{
		return;
	}

	for (FChildProfile& Profile : CurrentSaveGame->ChildProfiles)
	{
		if (Profile.ChildID == ActiveChildID)
		{
			Profile.Coins += Amount;
			SaveGame();
			return;
		}
	}
}

bool USuperfamilyGameInstance::SpendCoins(int32 Amount)
{
	if (!CurrentSaveGame || Amount <= 0)
	{
		return false;
	}

	for (FChildProfile& Profile : CurrentSaveGame->ChildProfiles)
	{
		if (Profile.ChildID == ActiveChildID)
		{
			if (Profile.Coins >= Amount)
			{
				Profile.Coins -= Amount;
				SaveGame();
				return true;
			}
			return false;
		}
	}
	return false;
}

int32 USuperfamilyGameInstance::GetCoins() const
{
	return GetActiveProfile().Coins;
}

int32 USuperfamilyGameInstance::GetXP() const
{
	return GetActiveProfile().TotalXP;
}

FString USuperfamilyGameInstance::GetLevelKey(int32 WorldID, int32 LevelID)
{
	return FString::Printf(TEXT("W%dL%d"), WorldID, LevelID);
}
