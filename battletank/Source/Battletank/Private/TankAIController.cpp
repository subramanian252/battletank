// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include"Tank.h"
#include"TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto possedtank = Cast<ATank>(InPawn);

		if (!ensure(possedtank)) { return; }

		possedtank->Ondeath.AddUniqueDynamic(this, &ATankAIController::OnTankdeath);
	}
}

void ATankAIController::OnTankdeath()
{
	if (!ensure(GetPawn())) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto playertank= (GetWorld()->GetFirstPlayerController()->GetPawn());
	auto controlledtank = (GetPawn());

	MoveToActor(playertank, acceptanceradius);
	
	auto aimmingcomponent = controlledtank->FindComponentByClass<UTankAimingComponent>();
	aimmingcomponent->Aimat(playertank->GetActorLocation());

	if (aimmingcomponent->getfiringstate() == Efiringstatus::standby)
	{
		aimmingcomponent->fire();
	}
}





