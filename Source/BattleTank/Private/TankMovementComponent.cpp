// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack || RightTrack)) { return; }

	//auto Name = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw: %f"), Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}


void UTankMovementComponent::IntentTurnRight(float Throw)
{
	if (!ensure(LeftTrack || RightTrack)) { return; }

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call super as we're replacing the functionality 

	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto ForwardThrow = FVector::DotProduct(AIForwardIntention , TankForward );
	IntendMoveForward(ForwardThrow);

	auto RightThrow = FVector::CrossProduct(TankForward,AIForwardIntention).Z;
	IntentTurnRight(RightThrow);
	//UE_LOG(LogTemp, Warning, TEXT(" Right: %f, Forward: %f"), RightThrow, ForwardThrow);
	

}

