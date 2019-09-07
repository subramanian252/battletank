// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class Efiringstatus :uint8
{
	reloading,
	firing,
	standby,
	OutOfAmmo
};

//forward declarations
class UTankBarrel;
class UTankTurretComponent;
class AAprojectile;

//holds the properties of barrel
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = State)
	Efiringstatus firingstate = Efiringstatus::reloading;
		
	


public:
	UFUNCTION(BlueprintCallable, Category = Setup)
	void initialize(UTankBarrel* Barrelset, UTankTurretComponent* Turretset);

	void Aimat(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = firing)
	void fire();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	Efiringstatus getfiringstate() const;

	UFUNCTION(BlueprintCallable, Category = firing)
	int GetRoundsLeft() const;

protected:
	

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	UTankBarrel* Barrel = nullptr;
	UTankTurretComponent* Turret = nullptr;

	void movebarreltoset(FVector aimdirection);

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	TSubclassOf<AAprojectile> projectileblueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float lastreloadtime = 3;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	int32 roundsleft = 20;

	double lastfiretime = 0;

	bool IsBarrelMoving();

	FVector Aimdirection;


		

};
