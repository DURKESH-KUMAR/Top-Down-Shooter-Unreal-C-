#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseBullet.generated.h"

UCLASS()
class CPPTUTORIALBASICS_API ABaseBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	class UNiagaraComponent* BulletFX;
	UPROPERTY(EditDefaultsOnly)
	class USphereComponent* CollisionSphere;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
