// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * 
 */
UCLASS(ClassGroup=(Custom),meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,Category=Input)
	void intendtomoveforward(float throwable);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void initialize(UTankTrack* lefttracktoset, UTankTrack* righttracktoset);

	UFUNCTION(BlueprintCallable, Category = Input)
	void intendtorotated(float throwable);

protected:
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed);

private:

	UTankTrack* lefttrack = nullptr;
	UTankTrack* righttrack = nullptr;
	

	
};
