#include "BaseBullet.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"


// Sets default values
ABaseBullet::ABaseBullet()
{
    BulletFX=CreateDefaultSubobject<UNiagaraComponent>(TEXT("Effects"));
    SetRootComponent(BulletFX);
    CollisionSphere=CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
    CollisionSphere->SetupAttachment(BulletFX);

    ProjectileMovement=CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->ProjectileGravityScale=0;
    PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseBullet::BeginPlay()
{
    Super::BeginPlay();
    CollisionSphere->OnComponentBeginOverlap.AddDynamic(this,&ABaseBullet::BeginOverlap);
}

// Called every frame
void ABaseBullet::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}


void ABaseBullet::BeginOverlap(UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,const FHitResult &SweepResult)
{
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,ImpactParticles,GetActorLocation());
    BulletHit();
    Destroy();
}

void ABaseBullet::BulletHit()
{

}

