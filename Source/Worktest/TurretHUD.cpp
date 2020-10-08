#include "TurretHUD.h"

ATurretHUD::ATurretHUD()
{

}

void ATurretHUD::BeginPlay()
{
	Super::BeginPlay();

	if (TurretUserWidget)
	{
		TurretUI = CreateWidget<UUserWidget>(GetWorld(), TurretUserWidget);
		if (TurretUI)
		{
			TurretUI->AddToViewport();
		}
	}
}

void ATurretHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ATurretHUD::DrawHUD()
{
	Super::DrawHUD();
}
