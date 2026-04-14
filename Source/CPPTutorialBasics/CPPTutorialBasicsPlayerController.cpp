#include "CPPTutorialBasicsPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"
#include "Engine/LocalPlayer.h"
#include "BaseMagicCharacter.h"

ACPPTutorialBasicsPlayerController::ACPPTutorialBasicsPlayerController()
{
}

void ACPPTutorialBasicsPlayerController::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter=Cast<ABaseMagicCharacter>(GetPawn());

	UE_LOG(LogTemp, Warning, TEXT("PlayerController BeginPlay"));

	// Add Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (DefaultMappingContext)
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
			UE_LOG(LogTemp, Warning, TEXT("Mapping Context Added"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("DefaultMappingContext is NULL"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("EnhancedInput Subsystem NOT found"));
	}
}

void ACPPTutorialBasicsPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UE_LOG(LogTemp, Warning, TEXT("SetupInputComponent Called"));

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(
    		MovementInput,
    		ETriggerEvent::Triggered,
    		this,
    		&ACPPTutorialBasicsPlayerController::Move
		);

		EnhancedInputComponent->BindAction(
    		FireInput,
    		ETriggerEvent::Triggered,
    		this,
    		&ACPPTutorialBasicsPlayerController::FireBullet
		);
		
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("EnhancedInputComponent NOT found"));
	}
}

void ACPPTutorialBasicsPlayerController::Move(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Move Called"));

	FVector2D MovementVector = Value.Get<FVector2D>();

	if (APawn* ControlledPawn = GetPawn())
	{
		// Get camera rotation
		FRotator Rotation = GetControlRotation();
		FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		// Directions
		FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Apply movement
		ControlledPawn->AddMovementInput(Forward, MovementVector.Y);
		ControlledPawn->AddMovementInput(Right, MovementVector.X);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Pawn is NULL"));
	}
}

void ACPPTutorialBasicsPlayerController::FireBullet(const FInputActionValue& Value)
{
	if(PlayerCharacter){
		PlayerCharacter->ShootBullet();
	}
}
