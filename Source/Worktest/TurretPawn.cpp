#include "TurretPawn.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "TurretHUD.h"
#include "TurretProjectile.h"

ATurretPawn::ATurretPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	TurretOffset = FVector(100.0f, 0.0f, 10.0f);
	MaxProjectiles = 20;
	selectedWeapon = 0;

	//Turret Body Parts
	TurretBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretBase"));
	RootComponent = TurretBase;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Mesh"));
	BodyMesh->SetupAttachment(RootComponent);

	GunBarrelBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Gun Base"));
	GunBarrelBase->SetupAttachment(RootComponent);

	GunBarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Gun"));
	GunBarrelMesh->SetupAttachment(GunBarrelBase);

	TurretMuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle Location"));
	TurretMuzzleLocation->SetupAttachment(GunBarrelMesh);

	//spring arm for the turret camera.
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GunBarrelBase);
	CameraBoom->TargetArmLength = 300.0f;

	//Third person camera for turret.
	TurretCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	TurretCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TurretCamera->bUsePawnControlRotation = false;
}

void ATurretPawn::BeginPlay()
{
	Super::BeginPlay();
	CurrentProjectiles = MaxProjectiles;
	CurrentTurretProjectile = BasicProjectile;
}

int ATurretPawn::GetCurrentProjectiles()
{
	return CurrentProjectiles;
}

int ATurretPawn::GetMaxProjectiles()
{
	return MaxProjectiles;
}

void ATurretPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Rotate();
}

void ATurretPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATurretPawn::OnFire);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ATurretPawn::ReloadTurret);
	PlayerInputComponent->BindAction("SwitchWeapon", IE_Pressed, this, &ATurretPawn::SwitchProjectile);
	PlayerInputComponent->BindAxis("Turn", this, &ATurretPawn::CalculateRotateInput);
}

int ATurretPawn::GetPlayerScore()
{
	return PlayerScore;
}

void ATurretPawn::SetPlayerScore(int value)
{
	PlayerScore += value;
}

void ATurretPawn::OnFire()
{
	if (CurrentTurretProjectile != NULL && CurrentProjectiles != 0)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			const FRotator SpawnRotation = GunBarrelBase->GetComponentRotation();
			const FVector SpawnLocation = ((TurretMuzzleLocation != nullptr) ?
				TurretMuzzleLocation->GetComponentLocation() 
				: GetActorLocation()) + SpawnRotation.RotateVector(TurretOffset);

			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
			World->SpawnActor<ATurretProjectile>(CurrentTurretProjectile, SpawnLocation, SpawnRotation, ActorSpawnParams);
			CurrentProjectiles--;
		}
	}
}

void ATurretPawn::SwitchProjectile()
{
	selectedWeapon++;
	GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Red, FString::FromInt(selectedWeapon));
	if (selectedWeapon == 1) { CurrentTurretProjectile = FireProjectile; }
	if (selectedWeapon == 2) { CurrentTurretProjectile = FrostProjectile; }
	if (selectedWeapon == 3) { CurrentTurretProjectile = PoisonProjectile; }
	if (selectedWeapon == 4) 
	{
		CurrentTurretProjectile = BasicProjectile;
		selectedWeapon = 0;
	}

}

void ATurretPawn::ReloadTurret()
{
	CurrentProjectiles = MaxProjectiles;
}

void ATurretPawn::CalculateRotateInput(float Value)
{
	float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(0, RotateAmount, 0);
	RotationDirection = FQuat(Rotation);
}

void ATurretPawn::Rotate()
{
	GunBarrelBase->AddLocalRotation(RotationDirection, true); //Only Rotate the GunBarrelBase(including the turret gun)
}