#include "BaseWeapon.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ABaseWeapon::ABaseWeapon()
{
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
 	
	PrimaryActorTick.bCanEverTick = true;

}
// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseWeapon::SetPlayerPointer(ACharacter* PlayerPtr)
{
	Player=PlayerPtr;
}
// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ABaseWeapon::WeaponShoot()
{
	
}

float ABaseWeapon::CalculateDamage(float Damages,float Multiplier)
{
	return Damages*Multiplier;
}

