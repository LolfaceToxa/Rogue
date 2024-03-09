// Copyright Phoinix-DEV

#include "SimplySettingsEditor/Public/SimplySettingsEditor.h"
#include "Editor.h"
#include "ISettingsModule.h"
#include "Kismet/GameplayStatics.h"
#include "ISettingsSection.h"
#include "SimplyConfigSettings.h"
#include "GameFramework/InputSettings.h"

#define LOCTEXT_NAMESPACE "FSimplySettingsEditorModule"

class UInputSettings;

void FSimplySettingsEditorModule::StartupModule()
{
	RegisterSettings();
}

void FSimplySettingsEditorModule::ShutdownModule()
{
	if (UObjectInitialized())
	{
		UnregisterSettings();
	}
}

void FSimplySettingsEditorModule::RegisterSettings()
{
	if (ISettingsModule *SettingModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		ISettingsSectionPtr SettingsSection = SettingModule->RegisterSettings(
			"Project", "Plugins", "SimplySettingsEditor",
			LOCTEXT("RuntimeSettingsName", "Simply Settings"),
			LOCTEXT("RuntimeSettingsDescription", "Configure the behaviour of Simply Settings"),
			GetMutableDefault<USimplyConfigSettings>());

		if (SettingsSection.IsValid())
		{
			SettingsSection->OnModified().BindRaw(this, &FSimplySettingsEditorModule::HandleSettingsSaved);
		}
	}
}

void FSimplySettingsEditorModule::UnregisterSettings()
{
	if (ISettingsModule *SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "SimplySettingsEditor");
	}
}

bool FSimplySettingsEditorModule::SupportsDynamicReloading()
{
	return true;
}

bool FSimplySettingsEditorModule::HandleSettingsSaved()
{
	UGameplayStatics::DeleteGameInSlot(USimplyConfigSettings::SaveGameName, 0);

	return true;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FSimplySettingsEditorModule, SimplySettingsEditor)
