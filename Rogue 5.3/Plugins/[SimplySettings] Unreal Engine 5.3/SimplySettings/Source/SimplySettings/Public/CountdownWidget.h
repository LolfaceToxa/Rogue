// Copyright Phoinix-DEV

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CountdownWidget.generated.h"

UCLASS()
class SIMPLYSETTINGS_API UCountdownWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FTimerHandle DestructionHandle;

	UPROPERTY(EditDefaultsOnly, Category="Setup")
	float Duration = 10;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category="Simply Settings")
	virtual float GetRemainingTime();
};
