// Copyright (c) 2024 Superfamily B.V. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SuperfamilyGameModeBase.generated.h"

/**
 * Base game mode for all Superfamily game modes
 * Provides common functionality for menu, world map, and level game modes
 */
UCLASS()
class SUPERFAMILY_API ASuperfamilyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASuperfamilyGameModeBase();

protected:
	virtual void BeginPlay() override;
};

/**
 * Game mode for the main menu
 */
UCLASS()
class SUPERFAMILY_API ASuperfamilyMainMenuGameMode : public ASuperfamilyGameModeBase
{
	GENERATED_BODY()

public:
	ASuperfamilyMainMenuGameMode();
};

/**
 * Game mode for the world map / level selection
 */
UCLASS()
class SUPERFAMILY_API ASuperfamilyWorldMapGameMode : public ASuperfamilyGameModeBase
{
	GENERATED_BODY()

public:
	ASuperfamilyWorldMapGameMode();
};

/**
 * Game mode for actual gameplay levels
 */
UCLASS()
class SUPERFAMILY_API ASuperfamilyLevelGameMode : public ASuperfamilyGameModeBase
{
	GENERATED_BODY()

public:
	ASuperfamilyLevelGameMode();

	/** Current world ID (1-based) */
	UPROPERTY(BlueprintReadOnly, Category = "Level")
	int32 WorldID = 1;

	/** Current level ID (1-based) */
	UPROPERTY(BlueprintReadOnly, Category = "Level")
	int32 LevelID = 1;

	/** Called when player completes the level */
	UFUNCTION(BlueprintCallable, Category = "Level")
	void OnLevelCompleted(int32 Stars, int32 Score);

	/** Called when player fails the level */
	UFUNCTION(BlueprintCallable, Category = "Level")
	void OnLevelFailed();

protected:
	virtual void BeginPlay() override;
};

/**
 * Game mode for boss encounters
 */
UCLASS()
class SUPERFAMILY_API ASuperfamilyBossGameMode : public ASuperfamilyLevelGameMode
{
	GENERATED_BODY()

public:
	ASuperfamilyBossGameMode();

	/** Number of questions in the boss encounter */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Boss")
	int32 TotalQuestions = 5;

	/** Current question index */
	UPROPERTY(BlueprintReadOnly, Category = "Boss")
	int32 CurrentQuestionIndex = 0;
};
