// Copyright Phoinix-DEV

#pragma once

#include "CoreMinimal.h"
#include "Components/Slider.h"
#include "SimplySettings_AudioSlider.generated.h"

/**
 * Audio Setting Slider - Per default changes Volume setting
 */
UCLASS()
class SIMPLYSETTINGS_API USimplySettings_AudioSlider : public USlider
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Setup")
	USoundMix *SoundMix;

	UPROPERTY(EditAnywhere, Category = "Setup")
	USoundClass *SoundClass;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float FadeInTime = .5f;

	virtual void OnWidgetRebuilt() override;

	UFUNCTION(BlueprintNativeEvent, Category = "Simply Settings")
	void OnNewValueSet(float NewValue);

	UFUNCTION(BlueprintNativeEvent, Category = "Simply Settings")
	float GetCurrentValue();

	UFUNCTION()
	virtual void RefreshProperties();

};
