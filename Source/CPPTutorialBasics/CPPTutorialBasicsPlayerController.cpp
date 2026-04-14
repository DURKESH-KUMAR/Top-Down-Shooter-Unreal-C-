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
		EnhancedInputComponent->BindAction(
    		FireInput,
    		ETriggerEvent::Started,
    		this,
    		&ACPPTutorialBasicsPlayerController::SetShootingTrue
		);
		EnhancedInputComponent->BindAction(
    		FireInput,
    		ETriggerEvent::Completed,
    		this,
    		&ACPPTutorialBasicsPlayerController::SetShootingFalse
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
    MovementRot = FVector(MovementVector, 0.f).Rotation();
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
	if(PlayerCharacter)
	{
		FVector direction=FVector(Value.Get<FVector2D>(),0);
		ShootRot=direction.Rotation();
		if(CanFire)
		{
			PlayerCharacter->ShootBullet();
			CanFire=false;

			FTimerDelegate Delegate=FTimerDelegate::CreateUObject(this, 
			&ACPPTutorialBasicsPlayerController::SetCanFire,
			true);
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle,Delegate,TimeBetweenFires,false);
		}
		PlayerCharacter->SetActorRotation(direction.Rotation());
		
	}
}

void ACPPTutorialBasicsPlayerController::SetCanFire(bool Value)
{
	CanFire=true;
}

void ACPPTutorialBasicsPlayerController::Tick(float DeltaTime)
{
	if(IsShooting){
		PlayerCharacter->SetActorRotation(ShootRot);
	}
	else{
		PlayerCharacter->SetActorRotation(MovementRot);
	}
	PlayerCharacter->SetActorRotation(ShootRot);
}


void ACPPTutorialBasicsPlayerController::SetShootingTrue()
{
	IsShooting=true;
}

void ACPPTutorialBasicsPlayerController::SetShootingFalse()
{
	IsShooting=false;
}


