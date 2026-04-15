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

	PlayerCharacter = Cast<ABaseMagicCharacter>(GetPawn());

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (DefaultMappingContext)
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ACPPTutorialBasicsPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MovementInput, ETriggerEvent::Triggered, this, &ACPPTutorialBasicsPlayerController::Move);

		EnhancedInputComponent->BindAction(FireInput, ETriggerEvent::Triggered, this, &ACPPTutorialBasicsPlayerController::FireBullet);

		EnhancedInputComponent->BindAction(FireInput, ETriggerEvent::Started, this, &ACPPTutorialBasicsPlayerController::SetShootingTrue);

		EnhancedInputComponent->BindAction(FireInput, ETriggerEvent::Completed, this, &ACPPTutorialBasicsPlayerController::SetShootingFalse);
	}
}

void ACPPTutorialBasicsPlayerController::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();

    APawn* ControlledPawn = GetPawn();

    if (ControlledPawn)
    {
        FVector MoveDir = FVector::ForwardVector * MovementVector.Y +
                          FVector::RightVector * MovementVector.X;

        ControlledPawn->AddMovementInput(FVector::ForwardVector, MovementVector.Y);
        ControlledPawn->AddMovementInput(FVector::RightVector, MovementVector.X);


        if (!MoveDir.IsNearlyZero())
        {
            if (PlayerCharacter)
            {
                PlayerCharacter->SetMovementRotation(MoveDir.Rotation());
            }
        }
    }
}

void ACPPTutorialBasicsPlayerController::FireBullet(const FInputActionValue& Value)
{
	FVector direction = FVector(Value.Get<FVector2D>(), 0);

	if (PlayerCharacter)
	{
		PlayerCharacter->ShootBullet(direction);
	}
}

void ACPPTutorialBasicsPlayerController::SetCanFire(bool Value)
{
	CanFire = true;
}

void ACPPTutorialBasicsPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACPPTutorialBasicsPlayerController::SetShootingTrue()
{
	if (PlayerCharacter)
	{
		PlayerCharacter->SetShootingTrue();
	}
}

void ACPPTutorialBasicsPlayerController::SetShootingFalse()
{
	if (PlayerCharacter)
	{
		PlayerCharacter->SetShootingFalse();
	}
}