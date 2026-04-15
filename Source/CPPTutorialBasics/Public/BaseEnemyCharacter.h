#pragma once

#include "CoreMinimal.h"
#include "BaseMagicCharacter.h"
#include "BaseEnemyCharacter.generated.h"

UCLASS()
class CPPTUTORIALBASICS_API ABaseEnemyCharacter : public ABaseMagicCharacter
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree* BTAsset;
};
