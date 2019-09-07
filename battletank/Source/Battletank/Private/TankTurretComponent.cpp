// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurretComponent.h"

void UTankTurretComponent::rotate(float relativevelocity)
{
	relativevelocity = FMath::Clamp<float>(relativevelocity, -1, +1);
	auto rotation = relativevelocity * maxdegeerespersecond * GetWorld()->DeltaTimeSeconds;
	auto newrotationchange = RelativeRotation.Yaw + rotation;
	SetRelativeRotation(FRotator(0,newrotationchange, 0));
}