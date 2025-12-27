// Copyright (c) 2024 Superfamily B.V. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SuperfamilyTypes.generated.h"

/**
 * Educational subjects available in the game
 * Aligned with Dutch primary school curriculum
 */
UENUM(BlueprintType)
enum class EQuestionSubject : uint8
{
	Taal        UMETA(DisplayName = "Taal"),         // Language/Reading
	Rekenen     UMETA(DisplayName = "Rekenen"),      // Mathematics
	Natuur      UMETA(DisplayName = "Natuur"),       // Nature/Science
	Engels      UMETA(DisplayName = "Engels")        // English
};

/**
 * Types of educational questions
 */
UENUM(BlueprintType)
enum class EQuestionType : uint8
{
	MultipleChoice  UMETA(DisplayName = "Multiple Choice"),
	TrueFalse       UMETA(DisplayName = "True/False"),
	Counting        UMETA(DisplayName = "Counting"),
	Matching        UMETA(DisplayName = "Matching"),
	Spelling        UMETA(DisplayName = "Spelling")
};

/**
 * Difficulty levels aligned with Dutch school groups
 * Groep 1-2: Kindergarten (age 4-6)
 * Groep 3-4: Primary school (age 6-8)
 */
UENUM(BlueprintType)
enum class EDifficultyLevel : uint8
{
	Groep1  UMETA(DisplayName = "Groep 1 (4-5 jaar)"),
	Groep2  UMETA(DisplayName = "Groep 2 (5-6 jaar)"),
	Groep3  UMETA(DisplayName = "Groep 3 (6-7 jaar)"),
	Groep4  UMETA(DisplayName = "Groep 4 (7-8 jaar)")
};

/**
 * Real-life mission categories
 */
UENUM(BlueprintType)
enum class EMissionCategory : uint8
{
	Huishouden  UMETA(DisplayName = "Huishouden"),   // Household tasks
	Sociaal     UMETA(DisplayName = "Sociaal"),      // Social interactions
	Creatief    UMETA(DisplayName = "Creatief"),     // Creative activities
	Natuur      UMETA(DisplayName = "Natuur"),       // Outdoor/Nature
	Leren       UMETA(DisplayName = "Leren")         // Learning extensions
};

/**
 * Mission completion status
 */
UENUM(BlueprintType)
enum class EMissionStatus : uint8
{
	Available           UMETA(DisplayName = "Beschikbaar"),
	InProgress          UMETA(DisplayName = "Bezig"),
	PendingApproval     UMETA(DisplayName = "Wacht op Goedkeuring"),
	Approved            UMETA(DisplayName = "Goedgekeurd"),
	Rejected            UMETA(DisplayName = "Afgekeurd"),
	Completed           UMETA(DisplayName = "Voltooid")
};

/**
 * Question data structure for educational content
 */
USTRUCT(BlueprintType)
struct SUPERFAMILY_API FQuestionData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Question")
	FString QuestionID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Question")
	EQuestionSubject Subject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Question")
	EQuestionType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Question")
	EDifficultyLevel Difficulty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Question")
	FText QuestionText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Question")
	TArray<FText> Answers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Question")
	int32 CorrectAnswerIndex = 0;

	/** Audio cue ID for voice-over (important for non-readers) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Question")
	FString AudioCueID;

	/** Optional image asset path */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Question")
	FString ImageAssetPath;

	FQuestionData()
		: Subject(EQuestionSubject::Taal)
		, Type(EQuestionType::MultipleChoice)
		, Difficulty(EDifficultyLevel::Groep1)
		, CorrectAnswerIndex(0)
	{
	}
};

/**
 * Mission data structure for real-life tasks
 */
USTRUCT(BlueprintType)
struct SUPERFAMILY_API FMissionData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission")
	FString MissionID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission")
	FText Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission")
	FText Instructions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission")
	EMissionCategory Category;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission")
	EDifficultyLevel MinAge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission")
	int32 XPReward = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission")
	int32 CoinReward = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission")
	bool bRequiresPhoto = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission")
	bool bRequiresParentApproval = true;

	/** Audio instruction cue for non-readers */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission")
	FString AudioInstructionsCue;

	FMissionData()
		: Category(EMissionCategory::Huishouden)
		, MinAge(EDifficultyLevel::Groep1)
		, XPReward(50)
		, CoinReward(10)
		, bRequiresPhoto(true)
		, bRequiresParentApproval(true)
	{
	}
};

/**
 * Level completion data for saving progress
 */
USTRUCT(BlueprintType)
struct SUPERFAMILY_API FLevelProgress
{
	GENERATED_BODY()

	UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Progress")
	bool bCompleted = false;

	UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Progress")
	int32 StarsEarned = 0;

	UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Progress")
	int32 HighScore = 0;

	UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Progress")
	int32 CoinsCollected = 0;

	UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Progress")
	int32 QuestionsCorrect = 0;

	UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Progress")
	int32 QuestionsTotal = 0;
};

/**
 * Subject progress for tracking educational advancement
 */
USTRUCT(BlueprintType)
struct SUPERFAMILY_API FSubjectProgress
{
	GENERATED_BODY()

	UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Progress")
	EQuestionSubject Subject;

	UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Progress")
	EDifficultyLevel CurrentLevel;

	UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Progress")
	int32 QuestionsAnswered = 0;

	UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Progress")
	int32 QuestionsCorrect = 0;

	UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Progress")
	float AverageResponseTime = 0.0f;

	FSubjectProgress()
		: Subject(EQuestionSubject::Taal)
		, CurrentLevel(EDifficultyLevel::Groep1)
	{
	}
};

/**
 * Child profile data for save system
 */
USTRUCT(BlueprintType)
struct SUPERFAMILY_API FChildProfile
{
	GENERATED_BODY()

	UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Profile")
	FString ChildID;

	UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Profile")
	FString DisplayName;

	UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Profile")
	int32 AgeGroup = 1;

	/** Serialized avatar customization as JSON */
	UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Profile")
	FString AvatarConfigJSON;

	UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Profile")
	int32 TotalXP = 0;

	UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Profile")
	int32 Coins = 0;

	UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Profile")
	int32 CurrentStreak = 0;

	UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Profile")
	FDateTime LastPlayedDate;

	/** Level progress keyed by "W{World}L{Level}" format */
	UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Profile")
	TMap<FString, FLevelProgress> LevelProgress;

	/** Subject progress keyed by subject enum name */
	UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Profile")
	TMap<FString, FSubjectProgress> SubjectProgress;

	UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Profile")
	TArray<FString> CompletedMissions;

	UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Profile")
	TArray<FString> UnlockedAchievements;
};
