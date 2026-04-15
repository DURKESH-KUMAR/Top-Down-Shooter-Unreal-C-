#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseMagicCharacter.generated.h"

class ABaseBullet;

UCLASS()
class CPPTUTORIALBASICS_API ABaseMagicCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseMagicCharacter();

	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	void SetMovementRotation(FRotator NewRotation);


protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UChildActorComponent* Weapon;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SpawnLocation;

	UPROPERTY(EditAnywhere)
	float HP=50;

	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const & DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser
	)override;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABaseBullet> BulletToSpawn;

	bool IsShooting = false;
	bool CanFire = true;

	FRotator ShootRot;
	FRotator MovementRot;

	UPROPERTY(EditAnywhere)
	float TimeBetweenFires = 0.2f;

	void ResetCanFire();

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	AActor* ShootBullet(FVector direction);

	void SetShootingTrue();
	void SetShootingFalse();

	UFUNCTION(BlueprintPure)
	FVector CalculateMovementBlending();
};