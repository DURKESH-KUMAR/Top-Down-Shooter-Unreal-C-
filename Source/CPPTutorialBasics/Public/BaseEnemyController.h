#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseEnemyController.generated.h"

UCLASS()
class CPPTUTORIALBASICS_API ABaseEnemyController : public AAIController
{
	GENERATED_BODY()
	virtual void BeginPlay();
	
};
