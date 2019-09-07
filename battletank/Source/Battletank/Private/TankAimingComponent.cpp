// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include"Aprojectile.h"
#include"TankTurretComponent.h"
#include "TankBarrel.h"




Efiringstatus UTankAimingComponent::getfiringstate() const
{
	return firingstate;
}

int UTankAimingComponent::GetRoundsLeft() const
{
	return roundsleft;
}

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::BeginPlay()
{
	lastfiretime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (roundsleft <= 0)
	{
		firingstate = Efiringstatus::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - lastfiretime) < lastreloadtime) 
	{
		firingstate = Efiringstatus::reloading;
	}
	else if (IsBarrelMoving())
	{
		firingstate = Efiringstatus::firing;
	}
	else
	{
		firingstate = Efiringstatus::standby;
	}
	
}


void UTankAimingComponent::Aimat(FVector HitLocation)
{
	FVector outlaunchvelocity;
	FVector startlocation = Barrel->GetSocketLocation(FName("projectile"));
	bool bhaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this, outlaunchvelocity, startlocation, HitLocation, LaunchSpeed,false,0.0f,0.0f, ESuggestProjVelocityTraceOption::DoNotTrace
	);
	
	if(bhaveAimSolution)
	{
		Aimdirection = outlaunchvelocity.GetSafeNormal();
		movebarreltoset(Aimdirection);
	}
	
}

void UTankAimingComponent::movebarreltoset(FVector aimdirection)
{
	auto Barrelrotator = Barrel->GetForwardVector().Rotation();
	auto aimrotator = aimdirection.Rotation();
	auto deltarotator = aimrotator - Barrelrotator;
	
	
	Barrel->elevate(deltarotator.Pitch);
	if (FMath::Abs(deltarotator.Yaw) < 180)
	{
		Turret->rotate(deltarotator.Yaw);
	}
	else
	{
		Turret->rotate(-deltarotator.Yaw);
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	auto barrel = Barrel->GetForwardVector();
	return !barrel.Equals(Aimdirection, 0.01);
	
}

void UTankAimingComponent::initialize(UTankBarrel* Barrelset, UTankTurretComponent* Turretset)
{

	Barrel = Barrelset;
	Turret = Turretset;
}

void UTankAimingComponent::fire()
{
	if (firingstate == Efiringstatus::standby || firingstate == Efiringstatus::firing)
	{
		auto projectile = GetWorld()->SpawnActor<AAprojectile>(
			projectileblueprint,
			Barrel->GetSocketLocation(FName("projectile")),
			Barrel->GetSocketRotation(FName("projectile"))
			);
		projectile->launchprojectile(LaunchSpeed);
		lastfiretime = FPlatformTime::Seconds();
		roundsleft--;
	}
}


