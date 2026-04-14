#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "CPPTutorialBasicsPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class ACPPTutorialBasicsPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACPPTutorialBasicsPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	// Input Mapping
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	// Movement Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MovementInput;
	// Fire Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* FireInput;

	// Movement Function
	void Move(const FInputActionValue& Value);

	void FireBullet(const FInputActionValue& Value);

	class ABaseMagicCharacter* PlayerCharacter;

	bool CanFire=true;
	UPROPERTY(EditAnywhere)
	float TimeBetweenFires=0.2f;
	void SetCanFire(bool Value);

	FRotator ShootRot;
	FRotator MovementRot;

	bool IsShooting;
	void SetShootingTrue();
	void SetShootingFalse();
	virtual void Tick(float DeltaTime)override;
};