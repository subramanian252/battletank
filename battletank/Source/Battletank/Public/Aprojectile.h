// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "Aprojectile.generated.h"


UCLASS()
class BATTLETANK_API AAprojectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAprojectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UProjectileMovementComponent* ProjectileMovement = nullptr;

	void launchprojectile(float speed);

	void TimerExpire();

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float delaytime = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float projectiledamage = 20.f;

	UPROPERTY(VisibleAnywhere,Category=input)
	UStaticMeshComponent* Collisionmesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = input)
	UParticleSystemComponent* Launchblast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = input)
	UParticleSystemComponent* ImpactBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = input)
	URadialForceComponent* ExplosionForce = nullptr;



private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

};
