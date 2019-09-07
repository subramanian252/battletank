// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine.h"



// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	currenthealth = startinghealth;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	int32 damagepoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 damagetoapply = FMath::Clamp(damagepoints, 0, currenthealth);

	currenthealth -= damagetoapply;
	if(currenthealth<=0)
	{
		Ondeath.Broadcast();
	}
	return damagetoapply;
}

float ATank::gethealthpercent() const
{
	return (float)currenthealth / (float)startinghealth;
}


	



