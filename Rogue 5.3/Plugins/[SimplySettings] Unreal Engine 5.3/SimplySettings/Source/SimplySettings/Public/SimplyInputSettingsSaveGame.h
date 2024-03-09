// Copyright Phoinix-DEV

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SimplyInputSettingsSaveGame.generated.h"

USTRUCT(BlueprintType)
struct FSimplySettingsContexts
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Simply Settings")
	TArray<UInputMappingContext *> Contexts;
};

USTRUCT(BlueprintType)
struct FAudioSetting
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Simply Settings")
	USoundMix *SoundMix = nullptr;

	UPROPERTY(EditAnywhere, Category = "Simply Settings")
	USoundClass *AudioClass = nullptr;

	UPROPERTY(EditAnywhere, Category = "Simply Settings")
	float Volume = 1;

	UPROPERTY(EditAnywhere, Category = "Simply Settings")
	float Pitch = 1;

	FAudioSetting()
	{
	}

	FAudioSetting(USoundMix *InSoundMix, USoundClass *InAudioClass, float InVolume = 1, float InPitch = 1)
	{
		this->SoundMix = InSoundMix;
		this->AudioClass = InAudioClass;
		this->Volume = InVolume;
		this->Pitch = InPitch;
	}
};

USTRUCT(BlueprintType)
struct FSimplySavedInputSettings
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Simply Settings")
	UInputMappingContext *Context;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Simply Settings")
	TArray<FEnhancedActionKeyMapping> Mappings;
};

UCLASS()
class SIMPLYSETTINGS_API USimplyInputSettingsSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Simply Settings")
	TArray<FSimplySavedInputSettings> SavedInputMappings;

	UPROPERTY(EditAnywhere, Category = "Simply Settings")
	TArray<FAudioSetting> AudioSettings;

	UPROPERTY(EditAnywhere, Category = "Simply Settings")
	TMap<FString, FString> CustomSettings;

	/**
	 * Input Stuff
	 */
	UFUNCTION(BlueprintCallable, Category = "Simply Settings")
	void LoadInputMappingsToSaveGame();

	UFUNCTION(BlueprintCallable, Category = "Simply Settings",
			  meta = (WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"))
	static void ApplySimplyInputSettings(UObject *WorldContextObject);

	/**
	 * Audio Stuff
	 */
	UFUNCTION(BlueprintCallable, Category = "Simply Settings")
	FAudioSetting GetVolumeSetting(USoundMix *InSoundMix, USoundClass *InAudioClass);

	UFUNCTION(BlueprintCallable, Category = "Simply Settings")
	void SetVolumeSetting(USoundMix *InSoundMix, USoundClass *InAudioClass, float InVolume);

	UFUNCTION(BlueprintCallable, Category = "Simply Settings")
	void SetPitchSetting(USoundMix *InSoundMix, USoundClass *InAudioClass, float InPitch);

	UFUNCTION(BlueprintCallable, Category = "Simply Settings",
			  meta = (WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"))
	static void ApplySimplySettingsAudio(UObject *WorldContextObject);

	/**
	 * Custom Settings
	 */
	UFUNCTION(BlueprintCallable, Category = "Simply Settings")
	static FString GetCustomSimplySetting(FString SettingKey);

	UFUNCTION(BlueprintCallable, Category = "Simply Settings")
	static int GetCustomSettingsAsInt(FString SettingKey);

	UFUNCTION(BlueprintCallable, Category = "Simply Settings")
	static int GetCustomSettingsAsFloat(FString SettingKey);

	UFUNCTION(BlueprintCallable, Category = "Simply Settings")
	static bool GetCustomSettingsAsBool(FString SettingKey);

	UFUNCTION(BlueprintCallable, Category = "Simply Settings")
	static void SetCustomSettings(FString SettingKey, FString Value);
};
