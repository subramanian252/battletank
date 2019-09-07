// Fill out your copyright notice in the Description page of Project Settings.


#include "Aprojectile.h"

// Sets default values
AAprojectile::AAprojectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collisionmesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("collisionmesh"));
	SetRootComponent(Collisionmesh);
	Collisionmesh->SetNotifyRigidBodyCollision(true);
	Collisionmesh->SetVisibility(false);

	Launchblast = CreateDefaultSubobject<UParticleSystemComponent>(FName("launchblast"));
	Launchblast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ProjectileMovement=	CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
	ProjectileMovement->bAutoActivate = false;

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("impactblast"));
	ImpactBlast->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

	ExplosionForce= CreateDefaultSubobject<URadialForceComponent>(FName("explosionforce"));
	ExplosionForce -> AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AAprojectile::BeginPlay()
{
	Super::BeginPlay();
	Collisionmesh->OnComponentHit.AddDynamic(this, &AAprojectile::OnHit);
	
}

void AAprojectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	Launchblast->Deactivate();
	ImpactBlast->Activate();
	ExplosionForce->FireImpulse();

	SetRootComponent(ImpactBlast);
	Collisionmesh->DestroyComponent();

	UGameplayStatics::ApplyRadialDamage(this, projectiledamage, GetActorLocation(), ExplosionForce->Radius, UDamageType::StaticClass(), TArray<AActor*>());
		
	FTimerHandle timer;
	GetWorld()->GetTimerManager().SetTimer(timer, this, &AAprojectile::TimerExpire, delaytime, false);
}

// Called every frame
void AAprojectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAprojectile::launchprojectile(float speed)
{
	
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector*speed);
	ProjectileMovement->Activate();
}

void AAprojectile::TimerExpire()
{
	Destroy();
}



