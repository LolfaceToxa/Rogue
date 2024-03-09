// Copyright Phoinix-DEV

#include "SimplySettings_AudioSlider.h"
#include "SimplyConfigSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundClass.h"

void USimplySettings_AudioSlider::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	USimplyConfigSettings *SimplySettings = GetMutableDefault<USimplyConfigSettings>();

	if (!SimplySettings->SimplySettingsChangedDelegate.IsBoundToObject(
			this))
	{
		SimplySettings->SimplySettingsChangedDelegate.AddUObject(
			this, &USimplySettings_AudioSlider::RefreshProperties);
	}

	USimplyInputSettingsSaveGame *CurrentSettings = USimplyConfigSettings::GetCachedSettings();
	if (IsValid(CurrentSettings))
	{
		FAudioSetting Setting = CurrentSettings->GetVolumeSetting(SoundMix, SoundClass);
		SetValue(Setting.Volume);
	}

	if (!OnValueChanged.IsAlreadyBound(this, &USimplySettings_AudioSlider::OnNewValueSet))
	{
		OnValueChanged.AddDynamic(this, &USimplySettings_AudioSlider::OnNewValueSet);
	}

	RefreshProperties();
}

void USimplySettings_AudioSlider::OnNewValueSet_Implementation(float NewValue)
{
	SetValue(NewValue);

	USimplyInputSettingsSaveGame *CurrentSettings = USimplyConfigSettings::GetCachedSettings();
	if (CurrentSettings)
	{
		CurrentSettings->SetVolumeSetting(SoundMix, SoundClass, NewValue);
		RefreshProperties();
	}
}

float USimplySettings_AudioSlider::GetCurrentValue_Implementation()
{
	USimplyInputSettingsSaveGame *CurrentSettings = USimplyConfigSettings::GetCachedSettings();
	if (CurrentSettings)
	{
		FAudioSetting Setting = CurrentSettings->GetVolumeSetting(SoundMix, SoundClass);
		return Setting.Volume;
	}
	return 0;
}

void USimplySettings_AudioSlider::RefreshProperties()
{
	if (SoundClass)
	{
		SetValue(GetCurrentValue());
		USimplyInputSettingsSaveGame *CurrentSettings = USimplyConfigSettings::GetCachedSettings();

		if (IsValid(CurrentSettings))
		{
			FAudioSetting Setting = CurrentSettings->GetVolumeSetting(SoundMix, SoundClass);
			UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SoundMix, SoundClass, Setting.Volume, Setting.Pitch,
													   FadeInTime);
			UGameplayStatics::PushSoundMixModifier(GetWorld(), SoundMix);
		}
	}
}
