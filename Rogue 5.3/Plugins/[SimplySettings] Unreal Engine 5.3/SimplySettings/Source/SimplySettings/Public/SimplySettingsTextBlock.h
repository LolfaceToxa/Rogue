// Copyright Phoinix-DEV

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "SimplySettingsTextBlock.generated.h"

UCLASS()
class SIMPLYSETTINGS_API USimplySettingsTextBlock : public UTextBlock
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	UInputMappingContext* Context;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	UInputAction* InputAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	FName MappingName;

	virtual void OnWidgetRebuilt() override;

	UFUNCTION(BlueprintCallable, Category="Simply Settings")
	virtual void Refresh();

	UFUNCTION(BlueprintCallable, Category="Simply Settings")
	void InitializeLabel(UInputMappingContext *InContext, UInputAction *InInputAction, FName InMappingName);

};
