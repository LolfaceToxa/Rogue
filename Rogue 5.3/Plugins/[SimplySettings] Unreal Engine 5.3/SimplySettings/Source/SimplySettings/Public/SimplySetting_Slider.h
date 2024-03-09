// Copyright Phoinix-DEV

#pragma once

#include "CoreMinimal.h"
#include "Components/Slider.h"
#include "SimplySetting_Slider.generated.h"

UCLASS()
class SIMPLYSETTINGS_API USimplySetting_Slider : public USlider
{
	GENERATED_BODY()

public:
	/** Differentiate between automatic assignment and manual one
	* This is required as there should be no userfeedback in the auto mode
	*/
	UPROPERTY(BlueprintReadWrite, Category="Simply Settings")
	bool ManualMode = true;

	virtual void OnWidgetRebuilt() override;

	UFUNCTION()
	void HandleNewValueSet(float NewValue);

	UFUNCTION(BlueprintNativeEvent, Category="Simply Settings")
	void OnNewValueSet(float NewValue);

	UFUNCTION(BlueprintNativeEvent, Category="Simply Settings")
	float GetCurrentValue();

	UFUNCTION()
	virtual void RefreshProperties();
};
