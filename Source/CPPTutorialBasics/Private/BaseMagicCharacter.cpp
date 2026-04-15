#include "BaseMagicCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "BaseWeapon.h"
#include "BaseBullet.h"
#include "Components/ChildActorComponent.h"
#include "Components/SceneComponent.h"
#include "TimerManager.h"

ABaseMagicCharacter::ABaseMagicCharacter()
{
	Weapon=CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(),TEXT("WeaponSocket"));
 	
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;

	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;

	SpawnLocation=CreateDefaultSubobject<USceneComponent>(TEXT("Bullet Spawn Point"));
	SpawnLocation->SetupAttachment(GetMesh());
}

void ABaseMagicCharacter::BeginPlay()
{
	Super::BeginPlay();

	ABaseWeapon* WeaponPtr=Cast<ABaseWeapon>(Weapon->GetChildActor());
	if(WeaponPtr){
		WeaponPtr->SetPlayerPointer(this);
	}
}

void ABaseMagicCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(IsShooting){
		SetActorRotation(ShootRot);
	}else{
		SetActorRotation(MovementRot);
	}
}

void ABaseMagicCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

AActor* ABaseMagicCharacter::ShootBullet(FVector direction)
{
	ShootRot = direction.Rotation();

	if(CanFire)
	{
		CanFire=false;

		FTimerHandle TimerHandle;

		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle,
			this,
			&ABaseMagicCharacter::ResetCanFire,
			TimeBetweenFires,
			false
		);
	}

	SetActorRotation(direction.Rotation());
		
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator=this;

	ABaseBullet* SpawnedActor = GetWorld()->SpawnActor<ABaseBullet>(
		BulletToSpawn,
		SpawnLocation->GetComponentLocation(),
		GetActorRotation(),
		SpawnParams);

	return SpawnedActor;
}

void ABaseMagicCharacter::ResetCanFire()
{
	CanFire = true;
}

void ABaseMagicCharacter::SetShootingTrue()
{
	IsShooting = true;
}

void ABaseMagicCharacter::SetShootingFalse()
{
	IsShooting = false;
}

FVector ABaseMagicCharacter::CalculateMovementBlending()
{
	FVector movement=MovementRot.Vector();
	FVector Shooting=ShootRot.Vector();
	float DotProd=FVector::DotProduct(movement,Shooting);
	FVector BlendVector=movement-Shooting*DotProd;
	FVector OutputVector=FVector(DotProd,BlendVector.Length(),0);
	return OutputVector*100;
}

float ABaseMagicCharacter::TakeDamage(float DamageAmount,
		struct FDamageEvent const & DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser)
{
	HP-=DamageAmount;
	if(HP<=0){
		Destroy();
	}
	return DamageAmount;
}