// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::intendtomoveforward(float throwable)
{

	lefttrack->setthrottle(throwable);
	righttrack->setthrottle(throwable);
}

void UTankMovementComponent::initialize(UTankTrack* lefttracktoset, UTankTrack* righttracktoset)
{
	lefttrack = lefttracktoset;
	righttrack = righttracktoset;
}

void UTankMovementComponent::intendtorotated(float throwable)
{
	lefttrack->setthrottle(throwable);
	righttrack->setthrottle(-throwable);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardintention = MoveVelocity.GetSafeNormal();

	auto move = FVector::DotProduct(TankForward, AIForwardintention);
	intendtomoveforward(move);

	auto rotate = FVector::CrossProduct(TankForward, AIForwardintention).Z;
	intendtorotated(rotate);
}
