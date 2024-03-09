// Copyright Phoinix-DEV

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerInput.h"
#include "UObject/NoExportTypes.h"
#include "InputMappingContext.h"
#include "EnhancedActionKeyMapping.h"
#include "SimplyInputSettingsSaveGame.h"
#include "SimplyConfigSettings.generated.h"

DECLARE_MULTICAST_DELEGATE(FSimplySettingsChangedDelegate);

UCLASS(config = SimplySettings, defaultconfig)
class SIMPLYSETTINGS_API USimplyConfigSettings : public UObject
{
	GENERATED_BODY()

public:
	// The name for the savegame
	inline const static FString SaveGameName = TEXT("SimplySettings");

	FSimplySettingsChangedDelegate SimplySettingsChangedDelegate;

	UPROPERTY(EditAnywhere, Category = "Simply Audio", Config)
	TArray<FAudioSetting> AudioSettings;

	// These keys are generally blocked
	UPROPERTY(EditAnywhere, Category = "Simply Bindings", Config)
	TArray<FInputChord> KeyBlacklist;

	UPROPERTY(EditAnywhere, Category = "Simply Bindings", Config, DisplayName = "Simply Settings Context")
	FSimplySettingsContexts Contexts;

	// Whether its allowed to have keys used to multiple Bindings
	UPROPERTY(EditAnywhere, Category = "Simply Bindings", Config)
	bool AllowMultiBinding = false;

	UPROPERTY(EditAnywhere, Category = "Simply Bindings", Config, meta = (EditCondition = "!AllowMultiBinding"))
	TArray<FSimplySettingsContexts> UniqueContextGroups;

	UPROPERTY(EditAnywhere, Category = "Custom Settings", Config)
	TMap<FString, FString> CustomSettings = TMap<FString, FString>();

	USimplyConfigSettings(const FObjectInitializer &ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Simply Settings")
	static void ForceUIUpdate();

	// Main function to loads, caches and applies all settings
	UFUNCTION(BlueprintCallable, Category = "Simply Settings",
			  meta = (WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"))
	static void LoadSimplySettings(UObject *WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Simply Settings",
			  meta = (WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"))
	static void SaveSimplySettings(UObject *WorldContextObject);

	// Clears the cached settings
	UFUNCTION(BlueprintCallable, Category = "Simply Settings")
	static void ClearCachedSettings();

	UFUNCTION(BlueprintCallable, Category = "Simply Settings")
	static USimplyInputSettingsSaveGame *GetCachedSettings();

protected:
	// Warning: This is added to the root to avoid garbage collection, it has to be cleared after usage to avoid leaks
	UPROPERTY()
	USimplyInputSettingsSaveGame *CachedSimplySettings;
};
