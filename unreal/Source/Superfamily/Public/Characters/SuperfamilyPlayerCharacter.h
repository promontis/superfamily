// Copyright (c) 2024 Superfamily B.V. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SuperfamilyPlayerCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
struct FInputActionValue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerJumped);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCoinCollected, int32, NewTotal);

/**
 * Player character for Superfamily 2.5D platformer
 * Constrained to XZ plane with side-scrolling camera
 */
UCLASS()
class SUPERFAMILY_API ASuperfamilyPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASuperfamilyPlayerCharacter();

	//~ Begin AActor Interface
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	//~ End AActor Interface

	//~ Begin APawn Interface
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	//~ End APawn Interface

	// ============================================
	// Movement (2.5D)
	// ============================================

	/** Move left/right in 2.5D space */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void Move2D(float AxisValue);

	/** Perform a jump */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void PerformJump();

	/** Check if character is facing right */
	UFUNCTION(BlueprintPure, Category = "Movement")
	bool IsFacingRight() const { return bIsFacingRight; }

	// ============================================
	// Collectibles
	// ============================================

	/** Add coins collected during level */
	UFUNCTION(BlueprintCallable, Category = "Collectibles")
	void CollectCoin(int32 Value = 1);

	/** Get coins collected this level */
	UFUNCTION(BlueprintPure, Category = "Collectibles")
	int32 GetSessionCoins() const { return SessionCoins; }

	// ============================================
	// Events
	// ============================================

	/** Called when player jumps */
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnPlayerJumped OnPlayerJumped;

	/** Called when a coin is collected */
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCoinCollected OnCoinCollected;

protected:
	// ============================================
	// Components
	// ============================================

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	/** Side-view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> SideViewCamera;

	// ============================================
	// Input
	// ============================================

	/** Default input mapping context */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	/** Move input action */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	/** Jump input action */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;

	/** Interact input action */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> InteractAction;

	// ============================================
	// Movement Settings
	// ============================================

	/** Base movement speed */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float MoveSpeed = 600.0f;

	/** Constrain movement to a single plane (2.5D) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	bool bConstrainToPlane = true;

	/** Plane normal for 2.5D constraint (Y = side-scrolling) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	FVector PlaneConstraintNormal = FVector(0.f, 1.f, 0.f);

	// ============================================
	// Camera Settings
	// ============================================

	/** Camera distance from character */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	float CameraDistance = 800.0f;

	/** Camera height offset */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	float CameraHeightOffset = 100.0f;

private:
	/** Handle move input */
	void HandleMoveInput(const FInputActionValue& Value);

	/** Handle jump input */
	void HandleJumpInput();

	/** Handle interact input */
	void HandleInteractInput();

	/** Update facing direction based on movement */
	void UpdateFacingDirection(float MoveDirection);

	/** Is the character facing right? */
	bool bIsFacingRight = true;

	/** Coins collected this session/level */
	int32 SessionCoins = 0;
};
