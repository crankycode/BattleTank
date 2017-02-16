// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force, and apply force to the tank.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// Set Throttle between -1 to 1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);

	// Max force per track, in Newton
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 400000.0f; // Assume 40 Tonne tank, and 1g accelleration

private:
	UTankTrack();

	virtual void BeginPlay() override;

	float MyThrottle = 0.0f;

	void ApplySidewaysForce();

	UFUNCTION(BlueprintCallable, Category = "Track")
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );
	
	void DriveTrack();
	
	float CurrentThrottle = 0;
};
