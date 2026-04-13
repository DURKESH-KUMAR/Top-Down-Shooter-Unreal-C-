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

	// Movement Function
	void Move(const FInputActionValue& Value);
};