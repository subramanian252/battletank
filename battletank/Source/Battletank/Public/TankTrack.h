// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UTankTrack();

	UFUNCTION(BlueprintCallable,Category=Input)
	void setthrottle(float throttle);

	UPROPERTY(EditDefaultsOnly)
	float maxforceonthtank = 90000000;

	float CurrentThrottle = 0;

	void DriveTrack();

	void ApplySidewaysForce();

	virtual void BeginPlay() override;


private:

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
