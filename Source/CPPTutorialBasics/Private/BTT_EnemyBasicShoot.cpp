#include "BTT_EnemyBasicShoot.h"
#include "BaseEnemyCharacter.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UBTT_EnemyBasicShoot::ExecuteTask(UBehaviorTreeComponent &OwnerComp,uint8 *NodeMemory)
{
    AAIController* controller=OwnerComp.GetAIOwner();
    ABaseEnemyCharacter* Enemy=Cast<ABaseEnemyCharacter>(controller->GetPawn());
    Enemy->ShootBullet(controller->GetPawn()->GetActorForwardVector());
    return EBTNodeResult::Succeeded;
}

