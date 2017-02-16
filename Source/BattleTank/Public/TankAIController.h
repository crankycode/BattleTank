// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()


protected:
	// How can the AI tank get
	UPROPERTY(EditDefaultsOnly)
	float AcceptanceRadius = 80000; // Consider EditDefaultsOnly

private:
	virtual void BeginPlay() override;
	
	virtual void SetPawn(APawn* InPawn) override;
	
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void OnPossedDeath();
	
};
