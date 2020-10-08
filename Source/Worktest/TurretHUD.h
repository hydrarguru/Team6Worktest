#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Components/WidgetComponent.h"
#include "TurretHUD.generated.h"


UCLASS()
class WORKTEST_API ATurretHUD : public AHUD
{
	GENERATED_BODY()
public:
	ATurretHUD();

	virtual void DrawHUD() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> TurretUserWidget;

private:
	UUserWidget* TurretUI;
};
