// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseMagicCharacter.generated.h"

UCLASS()
class CPPTUTORIALBASICS_API ABaseMagicCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseMagicCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Shoot();

	UPROPERTY(EditAnywhere)
	UChildActorComponent* Weapon;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};




