// Copyright (c) 2024 Superfamily B.V. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Types/SuperfamilyTypes.h"
#include "QuestionManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnQuestionAnswered, const FString&, QuestionID, bool, bCorrect, float, ResponseTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStreakUpdated, int32, CurrentStreak, int32, MaxStreak);

/**
 * Manages educational questions for Superfamily
 * Handles question loading, retrieval, answer validation, and progress tracking
 */
UCLASS()
class EDUCATIONSYSTEM_API UQuestionManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	//~ Begin USubsystem Interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	//~ End USubsystem Interface

	// ============================================
	// Question Loading
	// ============================================

	/** Load questions from a DataTable */
	UFUNCTION(BlueprintCallable, Category = "Education")
	void LoadQuestionsFromDataTable(UDataTable* QuestionTable);

	/** Load questions from CMS endpoint (async) */
	UFUNCTION(BlueprintCallable, Category = "Education")
	void LoadQuestionsFromCMS(const FString& Endpoint);

	/** Check if questions are loaded */
	UFUNCTION(BlueprintPure, Category = "Education")
	bool AreQuestionsLoaded() const { return QuestionPool.Num() > 0; }

	// ============================================
	// Question Retrieval
	// ============================================

	/** Get a random question matching criteria */
	UFUNCTION(BlueprintCallable, Category = "Education")
	FQuestionData GetQuestion(EQuestionSubject Subject, EDifficultyLevel Difficulty);

	/** Get a specific question by ID */
	UFUNCTION(BlueprintCallable, Category = "Education")
	FQuestionData GetQuestionByID(const FString& QuestionID);

	/** Get multiple questions for a session */
	UFUNCTION(BlueprintCallable, Category = "Education")
	TArray<FQuestionData> GetQuestionSet(EQuestionSubject Subject, EDifficultyLevel Difficulty, int32 Count);

	// ============================================
	// Answer Handling
	// ============================================

	/** Submit an answer for a question */
	UFUNCTION(BlueprintCallable, Category = "Education")
	bool SubmitAnswer(const FString& QuestionID, int32 AnswerIndex, float ResponseTime);

	/** Check if an answer is correct without submitting */
	UFUNCTION(BlueprintPure, Category = "Education")
	bool IsAnswerCorrect(const FString& QuestionID, int32 AnswerIndex) const;

	// ============================================
	// Adaptive Difficulty
	// ============================================

	/** Get recommended difficulty based on performance */
	UFUNCTION(BlueprintCallable, Category = "Education")
	EDifficultyLevel GetRecommendedDifficulty(EQuestionSubject Subject) const;

	// ============================================
	// Statistics
	// ============================================

	/** Get session statistics */
	UFUNCTION(BlueprintPure, Category = "Education")
	int32 GetSessionQuestionsAnswered() const { return SessionQuestionsAnswered; }

	UFUNCTION(BlueprintPure, Category = "Education")
	int32 GetSessionQuestionsCorrect() const { return SessionQuestionsCorrect; }

	UFUNCTION(BlueprintPure, Category = "Education")
	float GetSessionAccuracy() const;

	// ============================================
	// Events
	// ============================================

	/** Fired when a question is answered */
	UPROPERTY(BlueprintAssignable, Category = "Education")
	FOnQuestionAnswered OnQuestionAnswered;

	/** Fired when answer streak changes */
	UPROPERTY(BlueprintAssignable, Category = "Education")
	FOnStreakUpdated OnStreakUpdated;

protected:
	/** Pool of loaded questions */
	UPROPERTY()
	TArray<FQuestionData> QuestionPool;

	/** Session statistics */
	int32 SessionQuestionsAnswered = 0;
	int32 SessionQuestionsCorrect = 0;
	int32 CurrentStreak = 0;
	int32 MaxStreak = 0;

	/** Per-subject performance tracking */
	TMap<EQuestionSubject, float> SubjectAccuracy;

private:
	/** Find question by ID in pool */
	const FQuestionData* FindQuestion(const FString& QuestionID) const;
};
