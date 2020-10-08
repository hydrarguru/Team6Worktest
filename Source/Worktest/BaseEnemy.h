#pragma once
#include "Engine/Engine.h"
#include "GameFramework/Actor.h"
#include "BaseEnemy.generated.h"


UENUM()
enum ENEMY_TYPE
{
	NormalEnemy     UMETA(DisplayName = "NORMAL"),
	FireEnemy      UMETA(DisplayName = "FIRE"),
	FrostEnemy   UMETA(DisplayName = "FROST"),
	PoisonEnemy  UMETA(DisplayName = "POISON")
};

UCLASS()
class WORKTEST_API ABaseEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseEnemy();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* EnemyBaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Type")
	TEnumAsByte<ENEMY_TYPE> EnemyType;

	UFUNCTION()
	int GetEnemyType();

	UFUNCTION()
	void Die();

	UFUNCTION()
	int DecreaseHealth(int damage);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Type")
	int Health;

private:

protected:
	virtual void BeginPlay() override;
};
