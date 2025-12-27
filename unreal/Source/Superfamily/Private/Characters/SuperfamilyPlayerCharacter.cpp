// Copyright (c) 2024 Superfamily B.V. All Rights Reserved.

#include "Characters/SuperfamilyPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ASuperfamilyPlayerCharacter::ASuperfamilyPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	// Don't rotate when the controller rotates
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement for 2.5D platformer
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->bOrientRotationToMovement = false; // We control rotation manually
	Movement->RotationRate = FRotator(0.0f, 0.0f, 0.0f);
	Movement->JumpZVelocity = 600.0f;
	Movement->AirControl = 0.35f;
	Movement->MaxWalkSpeed = MoveSpeed;
	Movement->MinAnalogWalkSpeed = 20.0f;
	Movement->BrakingDecelerationWalking = 2000.0f;
	Movement->BrakingDecelerationFalling = 1500.0f;

	// Constrain to 2.5D plane
	Movement->bConstrainToPlane = bConstrainToPlane;
	Movement->SetPlaneConstraintNormal(PlaneConstraintNormal);
	Movement->SetPlaneConstraintEnabled(true);

	// Create camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f)); // Side view
	CameraBoom->TargetArmLength = CameraDistance;
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 3.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 0.0f, CameraHeightOffset);

	// Create camera
	SideViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCamera->bUsePawnControlRotation = false;
}

void ASuperfamilyPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Setup Enhanced Input
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (DefaultMappingContext)
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
}

void ASuperfamilyPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASuperfamilyPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Setup Enhanced Input bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Move action
		if (MoveAction)
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASuperfamilyPlayerCharacter::HandleMoveInput);
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ASuperfamilyPlayerCharacter::HandleMoveInput);
		}

		// Jump action
		if (JumpAction)
		{
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ASuperfamilyPlayerCharacter::HandleJumpInput);
		}

		// Interact action
		if (InteractAction)
		{
			EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ASuperfamilyPlayerCharacter::HandleInteractInput);
		}
	}
}

void ASuperfamilyPlayerCharacter::Move2D(float AxisValue)
{
	if (Controller && AxisValue != 0.0f)
	{
		// Move along X axis only (2.5D)
		const FVector Direction(1.0f, 0.0f, 0.0f);
		AddMovementInput(Direction, AxisValue);

		UpdateFacingDirection(AxisValue);
	}
}

void ASuperfamilyPlayerCharacter::PerformJump()
{
	if (CanJump())
	{
		Jump();
		OnPlayerJumped.Broadcast();
	}
}

void ASuperfamilyPlayerCharacter::CollectCoin(int32 Value)
{
	SessionCoins += Value;
	OnCoinCollected.Broadcast(SessionCoins);
}

void ASuperfamilyPlayerCharacter::HandleMoveInput(const FInputActionValue& Value)
{
	// Get movement value (1D axis for left/right)
	float MovementValue = Value.Get<float>();
	Move2D(MovementValue);
}

void ASuperfamilyPlayerCharacter::HandleJumpInput()
{
	PerformJump();
}

void ASuperfamilyPlayerCharacter::HandleInteractInput()
{
	// Interaction will be implemented via Blueprint for flexibility
	// This is a placeholder for C++ interaction logic if needed
	UE_LOG(LogTemp, Verbose, TEXT("Interact input received"));
}

void ASuperfamilyPlayerCharacter::UpdateFacingDirection(float MoveDirection)
{
	if (MoveDirection > 0.0f && !bIsFacingRight)
	{
		bIsFacingRight = true;
		SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
	}
	else if (MoveDirection < 0.0f && bIsFacingRight)
	{
		bIsFacingRight = false;
		SetActorRotation(FRotator(0.0f, 180.0f, 0.0f));
	}
}
