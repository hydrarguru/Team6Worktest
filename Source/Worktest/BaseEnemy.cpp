#include "BaseEnemy.h"
#include "Components/StaticMeshComponent.h"

ABaseEnemy::ABaseEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	EnemyType = NormalEnemy;
	Health = 100;
	EnemyBaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Enemy Base Mesh"));
}
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Die();
}

int ABaseEnemy::GetEnemyType()
{
	return EnemyType;
}

void ABaseEnemy::Die()
{
	if (Health <= 0)
	{
		this->Destroy(true);
	}
}

int ABaseEnemy::DecreaseHealth(int damage)
{
	return Health -= damage;
}

