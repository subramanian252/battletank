// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurretComponent.generated.h"


/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurretComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void rotate(float relativevelocity);

private:

	UPROPERTY(EditDefaultsOnly, Category = setup)
	float maxdegeerespersecond = 20.0f;


};

