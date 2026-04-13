// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

UCLASS()
class CPPTUTORIALBASICS_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float Damage;

	UFUNCTION(BlueprintCallable)
	void WeaponShoot();

	UFUNCTION(BlueprintPure)
	float CalculateDamage(float Damages,float Multiplier);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};








