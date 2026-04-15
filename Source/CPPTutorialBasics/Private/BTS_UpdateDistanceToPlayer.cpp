
#include "BTS_UpdateDistanceToPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTS_UpdateDistanceToPlayer::UBTS_UpdateDistanceToPlayer()
{
    NodeName="Update Distance To Player";
}


void UBTS_UpdateDistanceToPlayer::TickNode(UBehaviorTreeComponent& OwnerComp,uint8* NodeMemory,float DeltaSeconds)
{
    AActor* SelfActor=Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(SelfActorKey.SelectedKeyName));
    AActor* PlayerActor=Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(Player.SelectedKeyName));

    if(SelfActor && PlayerActor)
    {
        float Distance=FVector::Dist(SelfActor->GetActorLocation(),PlayerActor->GetActorLocation());
        OwnerComp.GetBlackboardComponent()->SetValueAsFloat(DistanceToPlayer.SelectedKeyName,Distance);
    }
}

