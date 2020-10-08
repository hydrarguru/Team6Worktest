#pragma once
#include "Engine/Engine.h"
#include "GameFramework/Actor.h"
#include "TurretPawn.h"
#include "TurretProjectile.generated.h"

UENUM()
enum ProjectileType
{
	Normal     UMETA(DisplayName = "NORMAL"),
	Fire      UMETA(DisplayName = "FIRE"),
	Frost   UMETA(DisplayName = "FROST"),
	Poison  UMETA(DisplayName = "POISON")
};


UCLASS()
class WORKTEST_API ATurretProjectile : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	class USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

private:
public:	
	ATurretProjectile();

	ATurretPawn* player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Type")
	TEnumAsByte<ProjectileType> projectileType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Projectile)
	class UParticleSystem* Particle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	int ProjectileDamage;

	UFUNCTION(BlueprintCallable)
	void UpdateScore();

	UFUNCTION(BlueprintCallable)
	void CheckHit(AActor* OtherActor);

	FORCEINLINE class USphereComponent* GetCollisionComp() const { return CollisionComp; }
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};
