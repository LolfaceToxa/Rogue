// Copyright Phoinix-DEV

#include "SimplyConfigSettings.h"
#include "GraphicsSettingsWidget.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputLibrary.h"
#include "SimplyInputSettingsSaveGame.h"
#include "Engine/World.h"
#include "InputSettingsWidget.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/KismetStringLibrary.h"

USimplyConfigSettings::USimplyConfigSettings(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
}

void USimplyConfigSettings::LoadSimplySettings(UObject *WorldContextObject)
{
	USimplyConfigSettings::ClearCachedSettings();
	USimplyConfigSettings *SimplySettings = GetMutableDefault<USimplyConfigSettings>();
	USimplyInputSettingsSaveGame *SaveGame = Cast<USimplyInputSettingsSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveGameName, 0));

	if (!SaveGame)
	{
		// There is no Input Save game - bad, lets create one
		USimplyInputSettingsSaveGame *Sg = Cast<USimplyInputSettingsSaveGame>(UGameplayStatics::CreateSaveGameObject(USimplyInputSettingsSaveGame::StaticClass()));
		Sg->AudioSettings = SimplySettings->AudioSettings;
		Sg->CustomSettings = SimplySettings->CustomSettings;
		Sg->LoadInputMappingsToSaveGame();
		SimplySettings->CachedSimplySettings = Sg;
		SaveSimplySettings(WorldContextObject);
	}
	else
	{
		SimplySettings->CachedSimplySettings = SaveGame;
	}

	SimplySettings->CachedSimplySettings->AddToRoot();
	SimplySettings->CachedSimplySettings->ApplySimplySettingsAudio(WorldContextObject);
	SimplySettings->CachedSimplySettings->ApplySimplyInputSettings(WorldContextObject);
	SimplySettings->ForceUIUpdate();
}

void USimplyConfigSettings::SaveSimplySettings(UObject *WorldContextObject)
{
	USimplyConfigSettings *SimplySettings = GetMutableDefault<USimplyConfigSettings>();
	if (SimplySettings && SimplySettings->CachedSimplySettings)
	{
		SimplySettings->CachedSimplySettings->LoadInputMappingsToSaveGame();
		UGameplayStatics::SaveGameToSlot(SimplySettings->CachedSimplySettings, SaveGameName, 0);
		SimplySettings->CachedSimplySettings->ApplySimplySettingsAudio(WorldContextObject);
		SimplySettings->CachedSimplySettings->ApplySimplyInputSettings(WorldContextObject);
	}
}

void USimplyConfigSettings::ClearCachedSettings()
{
	USimplyConfigSettings *SimplySettings = GetMutableDefault<USimplyConfigSettings>();
	if (SimplySettings->CachedSimplySettings)
	{
		SimplySettings->CachedSimplySettings->RemoveFromRoot();
		SimplySettings->CachedSimplySettings = nullptr;
	}
}

USimplyInputSettingsSaveGame *USimplyConfigSettings::GetCachedSettings()
{
	USimplyConfigSettings *SimplySettings = GetMutableDefault<USimplyConfigSettings>();
	return SimplySettings->CachedSimplySettings;
}

void USimplyConfigSettings::ForceUIUpdate()
{
	const USimplyConfigSettings *SimplySettings = GetDefault<USimplyConfigSettings>();
	if (SimplySettings->SimplySettingsChangedDelegate.IsBound())
	{
		SimplySettings->SimplySettingsChangedDelegate.Broadcast();
	}
}