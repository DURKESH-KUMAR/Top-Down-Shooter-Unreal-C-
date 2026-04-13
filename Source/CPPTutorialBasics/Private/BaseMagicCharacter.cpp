// Fill out your copyright notice in the Description page of Project Settings.
#include "BaseMagicCharacter.h"
// Sets default values
ABaseMagicCharacter::ABaseMagicCharacter()
{
	Weapon=CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(),TEXT("WeaponSocket"));
 	
	PrimaryActorTick.bCanEverTick = true;

}
// Called when the game starts or when spawned
void ABaseMagicCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseMagicCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseMagicCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void ABaseMagicCharacter::Shoot()
{
	
}

