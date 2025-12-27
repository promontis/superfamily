// Copyright (c) 2024 Superfamily B.V. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Types/SuperfamilyTypes.h"
#include "SuperfamilyGameInstance.generated.h"

class USuperFamilySaveGame;

/**
 * Central game instance for Superfamily
 * Manages save/load, profiles, settings, and global game state
 */
UCLASS()
class SUPERFAMILY_API USuperfamilyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	USuperfamilyGameInstance();

	//~ Begin UGameInstance Interface
	virtual void Init() override;
	virtual void Shutdown() override;
	//~ End UGameInstance Interface

	// ============================================
	// Profile Management
	// ============================================

	/** Get the currently active child profile */
	UFUNCTION(BlueprintCallable, Category = "Superfamily|Profile")
	FChildProfile GetActiveProfile() const;

	/** Set the active child profile by ID */
	UFUNCTION(BlueprintCallable, Category = "Superfamily|Profile")
	bool SetActiveProfile(const FString& ChildID);

	/** Get all available child profiles */
	UFUNCTION(BlueprintCallable, Category = "Superfamily|Profile")
	TArray<FChildProfile> GetAllProfiles() const;

	/** Create a new child profile */
	UFUNCTION(BlueprintCallable, Category = "Superfamily|Profile")
	bool CreateProfile(const FString& DisplayName, int32 AgeGroup);

	// ============================================
	// Save/Load System
	// ============================================

	/** Save the current game state to disk */
	UFUNCTION(BlueprintCallable, Category = "Superfamily|Save")
	bool SaveGame();

	/** Load the game state from disk */
	UFUNCTION(BlueprintCallable, Category = "Superfamily|Save")
	bool LoadGame();

	/** Check if a save file exists */
	UFUNCTION(BlueprintPure, Category = "Superfamily|Save")
	bool DoesSaveExist() const;

	// ============================================
	// Progress Tracking
	// ============================================

	/** Record level completion */
	UFUNCTION(BlueprintCallable, Category = "Superfamily|Progress")
	void RecordLevelCompletion(int32 WorldID, int32 LevelID, int32 Stars, int32 Score, int32 Coins);

	/** Get progress for a specific level */
	UFUNCTION(BlueprintPure, Category = "Superfamily|Progress")
	FLevelProgress GetLevelProgress(int32 WorldID, int32 LevelID) const;

	/** Check if a level is unlocked */
	UFUNCTION(BlueprintPure, Category = "Superfamily|Progress")
	bool IsLevelUnlocked(int32 WorldID, int32 LevelID) const;

	// ============================================
	// Currency & XP
	// ============================================

	/** Add XP to the active profile */
	UFUNCTION(BlueprintCallable, Category = "Superfamily|Currency")
	void AddXP(int32 Amount);

	/** Add coins to the active profile */
	UFUNCTION(BlueprintCallable, Category = "Superfamily|Currency")
	void AddCoins(int32 Amount);

	/** Spend coins (returns false if insufficient) */
	UFUNCTION(BlueprintCallable, Category = "Superfamily|Currency")
	bool SpendCoins(int32 Amount);

	/** Get current coin balance */
	UFUNCTION(BlueprintPure, Category = "Superfamily|Currency")
	int32 GetCoins() const;

	/** Get current XP */
	UFUNCTION(BlueprintPure, Category = "Superfamily|Currency")
	int32 GetXP() const;

	// ============================================
	// Settings
	// ============================================

	/** Get current audio culture (for voice-overs) */
	UFUNCTION(BlueprintPure, Category = "Superfamily|Settings")
	FString GetAudioCulture() const { return AudioCulture; }

	/** Set audio culture */
	UFUNCTION(BlueprintCallable, Category = "Superfamily|Settings")
	void SetAudioCulture(const FString& Culture) { AudioCulture = Culture; }

protected:
	/** Current save game data */
	UPROPERTY()
	TObjectPtr<USuperFamilySaveGame> CurrentSaveGame;

	/** Currently active child profile ID */
	UPROPERTY()
	FString ActiveChildID;

	/** Current audio culture for voice-overs */
	UPROPERTY()
	FString AudioCulture = TEXT("nl");

	/** Save slot name */
	static const FString SaveSlotName;

private:
	/** Helper to get level key string */
	static FString GetLevelKey(int32 WorldID, int32 LevelID);
};
