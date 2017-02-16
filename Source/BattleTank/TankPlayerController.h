// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

/**
 * Responsible for helping the player aim.
 */

//class ATank;
class UTankingAimingComponent;


UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:


protected:
	//UFUNCTION(BlueprintCallable, Category = "Setup")
	//ATank* GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

	UFUNCTION()
	void OnPossedDeath();

private:

	void AimTowardsCrosshair();
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaTime ) override;
	virtual void SetPawn(APawn* InPawn) override;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5f;
	
	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.33333f;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.0f;
		
	bool GetSightRayHitLocation(FVector &HitLoc) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;


};
