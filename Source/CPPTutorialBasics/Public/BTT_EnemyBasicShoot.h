#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_EnemyBasicShoot.generated.h"

UCLASS()
class CPPTUTORIALBASICS_API UBTT_EnemyBasicShoot : public UBTTaskNode
{
	GENERATED_BODY()
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp,uint8 *NodeMemory);
};
