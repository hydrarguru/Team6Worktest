#include "TurretProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BaseEnemy.h"
#include "Components/SphereComponent.h"

ATurretProjectile::ATurretProjectile()
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	RootComponent = CollisionComp;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = false;
	ProjectileMovement->bShouldBounce = true;

	InitialLifeSpan = 5.0f;
	projectileType = Normal;
	ProjectileDamage = 100;
}

void ATurretProjectile::UpdateScore()
{
	player = Cast<ATurretPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	player->SetPlayerScore(1);
}

void ATurretProjectile::CheckHit(AActor* OtherActor)
{
	ABaseEnemy* Enemy = Cast<ABaseEnemy>(OtherActor);
	if (Enemy != nullptr)
	{
		if (this->projectileType.GetValue() == Enemy->GetEnemyType())
		{
			if (Particle)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),Particle,Enemy->GetActorLocation(), Enemy->GetActorRotation(), true, EPSCPoolMethod::AutoRelease);
			}
			Enemy->DecreaseHealth(ProjectileDamage);
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Purple, "Enemy Health: " + FString::FromInt(Enemy->Health));
			UpdateScore();
		}
	}
}



