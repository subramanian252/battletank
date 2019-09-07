// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"


/**
 * 
 */
UCLASS( meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void elevate (float relativevelocity);

private:

	UPROPERTY(EditDefaultsOnly, Category = setup)
	float maxdegeerespersecond = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = setup)
	float maxelevation = 40.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = setup)
	float minelevation = 0.0f;
};
