#include "BaseBullet.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"

// Sets default values
ABaseBullet::ABaseBullet()
{
	BulletFX=CreateDefaultSubobject<UNiagaraComponent>(TEXT("Effects"));
	SetRootComponent(BulletFX);
	CollisionSphere=CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	CollisionSphere->SetupAttachment(BulletFX);

 	
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

