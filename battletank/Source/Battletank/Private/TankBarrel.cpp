// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::elevate(float relativevelocity)
{
	relativevelocity = FMath::Clamp<float>(relativevelocity, -1, +1);
	auto elevationchange = relativevelocity * maxdegeerespersecond * GetWorld()->DeltaTimeSeconds;
	auto rawelevationchange = RelativeRotation.Pitch + elevationchange;
	auto  elevation = FMath::Clamp<float>(rawelevationchange, minelevation, maxelevation);
	SetRelativeRotation(FRotator(elevation, 0, 0));

	
}