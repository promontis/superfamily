// Copyright (c) 2024 Superfamily B.V. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "RNUEBridgeSubsystem.generated.h"

/**
 * Message types for RNUE communication
 */
UENUM(BlueprintType)
enum class ERNUEMessageType : uint8
{
	// Game -> React Native
	GameReady               UMETA(DisplayName = "Game Ready"),
	LevelCompleted          UMETA(DisplayName = "Level Completed"),
	LevelFailed             UMETA(DisplayName = "Level Failed"),
	QuestionAnswered        UMETA(DisplayName = "Question Answered"),
	MissionStarted          UMETA(DisplayName = "Mission Started"),
	MissionPhotoRequired    UMETA(DisplayName = "Mission Photo Required"),
	MissionCompleted        UMETA(DisplayName = "Mission Completed"),
	ProfileDataUpdated      UMETA(DisplayName = "Profile Data Updated"),
	PauseRequested          UMETA(DisplayName = "Pause Requested"),

	// React Native -> Game
	StartLevel              UMETA(DisplayName = "Start Level"),
	PauseGame               UMETA(DisplayName = "Pause Game"),
	ResumeGame              UMETA(DisplayName = "Resume Game"),
	PhotoCaptured           UMETA(DisplayName = "Photo Captured"),
	ParentApproval          UMETA(DisplayName = "Parent Approval"),
	ProfileSelected         UMETA(DisplayName = "Profile Selected"),
	SettingsChanged         UMETA(DisplayName = "Settings Changed")
};

/**
 * RNUE message structure
 */
USTRUCT(BlueprintType)
struct RNUEBRIDGE_API FRNUEMessage
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "RNUE")
	ERNUEMessageType Type;

	/** JSON payload string */
	UPROPERTY(BlueprintReadWrite, Category = "RNUE")
	FString Payload;

	/** Correlation ID for request/response matching */
	UPROPERTY(BlueprintReadWrite, Category = "RNUE")
	FString CorrelationID;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRNUEMessageReceived, const FRNUEMessage&, Message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnLevelStartRequested, int32, WorldID, int32, LevelID, const FString&, ChildID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPhotoReceived, const FString&, MissionID, const FString&, PhotoPath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnParentApprovalReceived, const FString&, MissionID, bool, bApproved, const FString&, Comment);

/**
 * Bridge subsystem for communication between Unreal Engine and React Native
 * Uses RNUE (React Native for Unreal Engine) pattern
 */
UCLASS()
class RNUEBRIDGE_API URNUEBridgeSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	//~ Begin USubsystem Interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	//~ End USubsystem Interface

	// ============================================
	// Outgoing Messages (UE5 -> React Native)
	// ============================================

	/** Send a message to React Native */
	UFUNCTION(BlueprintCallable, Category = "RNUE")
	void SendToReactNative(const FRNUEMessage& Message);

	/** Notify that the game is ready */
	UFUNCTION(BlueprintCallable, Category = "RNUE")
	void NotifyGameReady();

	/** Notify level completion */
	UFUNCTION(BlueprintCallable, Category = "RNUE")
	void NotifyLevelCompleted(int32 WorldID, int32 LevelID, int32 Stars, int32 XPEarned, int32 CoinsCollected);

	/** Notify level failure */
	UFUNCTION(BlueprintCallable, Category = "RNUE")
	void NotifyLevelFailed(int32 WorldID, int32 LevelID);

	/** Request photo capture for mission */
	UFUNCTION(BlueprintCallable, Category = "RNUE")
	void RequestPhotoCapture(const FString& MissionID);

	/** Request parent approval for mission */
	UFUNCTION(BlueprintCallable, Category = "RNUE")
	void RequestParentApproval(const FString& MissionID, const FString& PhotoURL);

	/** Notify profile data has been updated */
	UFUNCTION(BlueprintCallable, Category = "RNUE")
	void NotifyProfileUpdated(const FString& ChildID);

	// ============================================
	// Incoming Messages (React Native -> UE5)
	// ============================================

	/** Called from native code when a message is received from React Native */
	UFUNCTION(BlueprintCallable, Category = "RNUE")
	void OnMessageFromReactNative(const FString& MessageJSON);

	// ============================================
	// Events
	// ============================================

	/** Generic message received event */
	UPROPERTY(BlueprintAssignable, Category = "RNUE")
	FOnRNUEMessageReceived OnMessageReceived;

	/** Specific event: Level start requested */
	UPROPERTY(BlueprintAssignable, Category = "RNUE")
	FOnLevelStartRequested OnLevelStartRequested;

	/** Specific event: Photo received from camera */
	UPROPERTY(BlueprintAssignable, Category = "RNUE")
	FOnPhotoReceived OnPhotoReceived;

	/** Specific event: Parent approval received */
	UPROPERTY(BlueprintAssignable, Category = "RNUE")
	FOnParentApprovalReceived OnParentApprovalReceived;

protected:
	/** Generate a unique correlation ID */
	FString GenerateCorrelationID();

	/** Parse incoming JSON message */
	bool ParseMessage(const FString& JSON, FRNUEMessage& OutMessage);

	/** Build JSON payload for outgoing message */
	FString BuildPayload(const TMap<FString, FString>& Data);

private:
	/** Counter for correlation IDs */
	int32 CorrelationCounter = 0;
};
