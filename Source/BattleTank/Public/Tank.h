 // Copyright EmbraceIT Ltd.

#pragma once

//#include "TankAimingComponent.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Put new include above

// Forward declarations
//class UTankBarrel;
//class UTankTurret;
//class UProjectileMovementComponent;
//class UTankMovementComponent;
//class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Return current health as a percentage of starting health, between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercentage() const;
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);
	FTankDelegate OnDeath;

	virtual void BeginPlay() override;

private:

	// Sets default values for this pawn's properties
	ATank();
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth; // Initialised in BeginPlay()

	
};
