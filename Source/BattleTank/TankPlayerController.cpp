// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"
#include "Tank.h"
#define OUT

// Tick
	// Super
	// AimTowardsCrosshair();


void ATankPlayerController::BeginPlay()
{
	//FHitResult NewHitResult;
	//ActorLineTraceSingle(NewHitResult, GetPawn()->GetActorLocation(),FVector(100,100,100), EVisibility,)

	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
		FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// TODO Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossedDeath);
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );
	AimTowardsCrosshair();
}





//ATank* ATankPlayerController::GetControlledTank() const
//{
//
//	return GetPawn();
//}

// Start the tank moving the barrel so that a shot would hit where
// the crosshair intersects the world
void ATankPlayerController::AimTowardsCrosshair()
{

	if (!(GetPawn())) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);

	FVector HitLocation; // Out parameter
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	//UE_LOG(LogTemp, Warning, TEXT("hit: %f"), bGotHitLocation);
	if (bGotHitLocation)
	{
		AimingComponent->AimAt(HitLocation);
		//GetControlledTank()->AimAt(HitLocation);
		//TODO  Tell controlled tank to aim at the location 
	}
}

// Get world location if linetrace through crosshair, True if it hits the landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(CrossHairXLocation * ViewportSizeX, CrossHairYLocation * ViewportSizeY);
	FVector LookDirection;
	// CamaraWorldLocation is Camara Location, WorldDirection is where u r looking

	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace along that LookDirection, and see what we hit (up to max range)
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	return false;
}

// De-Project" the screen position of the crosshair to a world direction
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	// Too be discard
	FVector CamaraWorldLocation;

	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CamaraWorldLocation,
		LookDirection
		);
}
bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
			OUT HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Camera)
		)
	{
		// Set hit location
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}

void ATankPlayerController::OnPossedDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Tank is Dead Receive from TankPlayerController"));
	this->GetPawn()->DetachFromControllerPendingDestroy();
	this->StartSpectatingOnly();

}


