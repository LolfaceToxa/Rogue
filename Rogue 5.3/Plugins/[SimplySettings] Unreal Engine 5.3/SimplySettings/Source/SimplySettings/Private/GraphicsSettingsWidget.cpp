// Copyright Phoinix-DEV

#include "GraphicsSettingsWidget.h"
#include "SimplyConfigSettings.h"
#include "Blueprint/WidgetTree.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/KismetStringLibrary.h"

void UGraphicsSettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	const UGameUserSettings *GameUserSettings = UGameUserSettings::GetGameUserSettings();
	CachedResScale = GameUserSettings->GetResolutionScaleNormalized();
}

void UGraphicsSettingsWidget::SaveGraphicSettings()
{
	UGameUserSettings *GameUserSettings = UGameUserSettings::GetGameUserSettings();

	if (GameUserSettings->IsScreenResolutionDirty() || GameUserSettings->IsFullscreenModeDirty())
	{
		// We apply everything, just to make sure everything works together
		GameUserSettings->ApplyResolutionSettings(false);
		GameUserSettings->ApplyNonResolutionSettings();
		VideoSecurityCheck();
		// We do not save yet, the user has to confirm first over the security check
		return;
	}
	CachedResScale = GameUserSettings->GetResolutionScaleNormalized();
	GameUserSettings->ApplySettings(false);
}

void UGraphicsSettingsWidget::DiscardGraphicSettings()
{
	// Get the game user settings object
	UGameUserSettings *GameUserSettings = UGameUserSettings::GetGameUserSettings();

	// Load the settings from the config file
	GameUserSettings->LoadSettings(true);
	GameUserSettings->SetResolutionScaleNormalized(CachedResScale);

	GameUserSettings->ApplyResolutionSettings(false);
	GameUserSettings->ApplyNonResolutionSettings();
	USimplyConfigSettings::ForceUIUpdate();
}

FIntPoint UGraphicsSettingsWidget::ResStringToIntPoint(FString ResString)
{
	FString XString;
	FString YString;
	ResString.Split(" ", &XString, &YString);
	XString = XString.Replace(TEXT("X="), TEXT(""));
	YString = YString.Replace(TEXT("Y="), TEXT(""));
	int X = UKismetStringLibrary::Conv_StringToInt(XString);
	int Y = UKismetStringLibrary::Conv_StringToInt(YString);
	return FIntPoint(X, Y);
}
