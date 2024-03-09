// Copyright Phoinix-DEV


#include "SimplySettings_ComboBoxString.h"
#include "SimplyConfigSettings.h"

void USimplySettings_ComboBoxString::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	USimplyConfigSettings* SimplySettings = GetMutableDefault<USimplyConfigSettings>();

	if (!OnSelectionChanged.IsAlreadyBound(this, &USimplySettings_ComboBoxString::HandleSelect))
	{
		OnSelectionChanged.AddDynamic(this, &USimplySettings_ComboBoxString::HandleSelect);
	}

	if (!SimplySettings->SimplySettingsChangedDelegate.IsBoundToObject(this))
	{
		SimplySettings->SimplySettingsChangedDelegate.AddUObject(
			this, &USimplySettings_ComboBoxString::InitializeOptions);
	}
	InitializeOptions();
}

void USimplySettings_ComboBoxString::HandleSelect(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (ManualMode)
	{
		OnSelect(FName(SelectedItem), SelectionType);
	}
}
