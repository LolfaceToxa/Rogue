// Copyright Phoinix-DEV


#include "SimplySetting_Slider.h"
#include "SimplyConfigSettings.h"
#include "SimplySettings_AudioSlider.h"

void USimplySetting_Slider::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	USimplyConfigSettings* SimplySettings = GetMutableDefault<USimplyConfigSettings>();

	if (!SimplySettings->SimplySettingsChangedDelegate.IsBoundToObject(
		this))
	{
		SimplySettings->SimplySettingsChangedDelegate.AddUObject(
			this, &USimplySetting_Slider::RefreshProperties);
	}

	if (!OnValueChanged.IsAlreadyBound(this, &USimplySetting_Slider::HandleNewValueSet))
	{
		OnValueChanged.AddDynamic(this, &USimplySetting_Slider::HandleNewValueSet);
	}

	RefreshProperties();
}

void USimplySetting_Slider::HandleNewValueSet(float NewValue)
{
	if (ManualMode)
	{
		OnNewValueSet(NewValue);
	}
}

float USimplySetting_Slider::GetCurrentValue_Implementation()
{
	return 0;
}

void USimplySetting_Slider::OnNewValueSet_Implementation(float NewValue)
{
}

void USimplySetting_Slider::RefreshProperties()
{
	ManualMode = false;
	SetValue(GetCurrentValue());
	ManualMode = true;
}
