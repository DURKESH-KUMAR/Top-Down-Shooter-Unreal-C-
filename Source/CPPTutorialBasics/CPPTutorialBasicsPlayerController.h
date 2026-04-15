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

	void SetShootingTrue();
	void SetShootingFalse();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MovementInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* FireInput;

	void Move(const FInputActionValue& Value);
	void FireBullet(const FInputActionValue& Value);

	class ABaseMagicCharacter* PlayerCharacter;

	bool CanFire = true;

	UPROPERTY(EditAnywhere)
	float TimeBetweenFires = 0.2f;

	void SetCanFire(bool Value);

	UPROPERTY(EditDefaultsOnly)
	float speed;

	UPROPERTY(BlueprintReadOnly)
	bool IsShooting;

	virtual void Tick(float DeltaTime) override;
};