// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"
#include "Tank.h" // So we can impliment OnDeath
// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// TODO Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedDeath);
	}
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto* ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }

		MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in cm

		auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

		// TODO Move towards the player
		// Aim towards the player
		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		// TODO fix firing
		//AIContronlledTank->Fire(); // TODO limit firing rate

		// if aiming or locked
		if (AimingComponent->GetFiringState() == EFiringState::Locked)
		{
			AimingComponent->Fire();
		}
}

void ATankAIController::OnPossedDeath()
{
	if (!GetPawn()) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
	UE_LOG(LogTemp, Warning, TEXT("Tank is Dead Receive from TankAIController"));
}



