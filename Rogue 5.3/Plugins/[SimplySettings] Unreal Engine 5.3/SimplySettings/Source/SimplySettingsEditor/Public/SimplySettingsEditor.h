// Copyright Phoinix-DEV

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FSimplySettingsEditorModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void RegisterSettings();
	void UnregisterSettings();

	virtual bool SupportsDynamicReloading() override;
	bool HandleSettingsSaved();
};
