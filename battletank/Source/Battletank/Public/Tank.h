// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Engine.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);


class UTankBarrel;
class UTankTurretComponent;
class AAprojectile;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()
	// Sets default values for this pawn's properties
	ATank();

public:

	virtual void BeginPlay()override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditDefaultsOnly, Category = setup)
	int32 startinghealth = 100;

	FTankDelegate Ondeath;

	UPROPERTY(VisibleAnywhere, Category = setup)
	int32 currenthealth;

	UFUNCTION(BlueprintPure,Category=setup)
	float gethealthpercent() const;


};
