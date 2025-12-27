// Copyright (c) 2024 Superfamily B.V. All Rights Reserved.

#include "Core/SuperfamilyGameModeBase.h"
#include "Core/SuperfamilyGameInstance.h"
#include "Kismet/GameplayStatics.h"

// ============================================
// ASuperfamilyGameModeBase
// ============================================

ASuperfamilyGameModeBase::ASuperfamilyGameModeBase()
{
	// Defaults will be set in Blueprint subclasses
}

void ASuperfamilyGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

// ============================================
// ASuperfamilyMainMenuGameMode
// ============================================

ASuperfamilyMainMenuGameMode::ASuperfamilyMainMenuGameMode()
{
	// No pawn needed in main menu
	DefaultPawnClass = nullptr;
}

// ============================================
// ASuperfamilyWorldMapGameMode
// ============================================

ASuperfamilyWorldMapGameMode::ASuperfamilyWorldMapGameMode()
{
	// No pawn needed in world map
	DefaultPawnClass = nullptr;
}

// ============================================
// ASuperfamilyLevelGameMode
// ============================================

ASuperfamilyLevelGameMode::ASuperfamilyLevelGameMode()
{
	// Pawn class will be set to player character Blueprint
	// DefaultPawnClass = ASuperfamilyPlayerCharacter::StaticClass();
}

void ASuperfamilyLevelGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Parse level name to get WorldID and LevelID
	// Expected format: L_W01_Level05 or similar
	FString LevelName = GetWorld()->GetMapName();
	LevelName.RemoveFromStart(TEXT("UEDPIE_0_")); // Remove PIE prefix if present

	// Extract world and level numbers from name
	// Format: L_W{World}_Level{Level} or L_W{World}_Level{Level}_Boss
	FRegexPattern Pattern(TEXT("W(\\d+)_Level(\\d+)"));
	FRegexMatcher Matcher(Pattern, LevelName);

	if (Matcher.FindNext())
	{
		WorldID = FCString::Atoi(*Matcher.GetCaptureGroup(1));
		LevelID = FCString::Atoi(*Matcher.GetCaptureGroup(2));
	}

	UE_LOG(LogTemp, Log, TEXT("Level started: World %d, Level %d"), WorldID, LevelID);
}

void ASuperfamilyLevelGameMode::OnLevelCompleted(int32 Stars, int32 Score)
{
	USuperfamilyGameInstance* GameInstance = Cast<USuperfamilyGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		// Get coins collected from player character
		// (This will be expanded when player character is fully implemented)
		int32 CoinsCollected = 0;

		GameInstance->RecordLevelCompletion(WorldID, LevelID, Stars, Score, CoinsCollected);
	}

	UE_LOG(LogTemp, Log, TEXT("Level completed: %d stars, %d score"), Stars, Score);
}

void ASuperfamilyLevelGameMode::OnLevelFailed()
{
	UE_LOG(LogTemp, Log, TEXT("Level failed"));

	// Respawn or return to world map - will be implemented in Blueprint
}

// ============================================
// ASuperfamilyBossGameMode
// ============================================

ASuperfamilyBossGameMode::ASuperfamilyBossGameMode()
{
	TotalQuestions = 5;
	CurrentQuestionIndex = 0;
}
