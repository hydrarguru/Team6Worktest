#pragma once
#include "Engine/Engine.h"
#include "GameFramework/Character.h"
#include "TurretPawn.generated.h"

class UStaticMeshComponent;

UCLASS()
class WORKTEST_API ATurretPawn : public APawn
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* TurretBase;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* GunBarrelBase;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* GunBarrelMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* TurretMuzzleLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TurretCamera;

private:
	UPROPERTY(EditAnywhere, Category = "Turret")
	int MaxProjectiles;

	UPROPERTY(EditAnywhere, Category = "Turret")
	int CurrentProjectiles;

	UPROPERTY(EditAnywhere, Category = Gameplay)
	int PlayerScore;

	UFUNCTION()
	void SwitchProjectile();

	int selectedWeapon;

public:
	ATurretPawn();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure, Category = "Turret")
	int GetCurrentProjectiles(); //Accessor for current amount projectiles

	UFUNCTION(BlueprintPure, Category = "Turret")
	int GetMaxProjectiles(); //Accessor for max amount projectiles

	UFUNCTION(BlueprintPure, Category = Gameplay)
	int GetPlayerScore(); //Accessor for the score.

	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void SetPlayerScore(int value);

	void OnFire();
	void ReloadTurret();
	void CalculateRotateInput(float Value);
	void Rotate();

	FQuat RotationDirection;
	float RotateSpeed = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector TurretOffset;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ATurretProjectile> CurrentTurretProjectile;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ATurretProjectile> BasicProjectile;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ATurretProjectile> FireProjectile;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ATurretProjectile> FrostProjectile;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ATurretProjectile> PoisonProjectile;
};
