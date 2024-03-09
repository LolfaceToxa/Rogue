// Fill out your copyright notice in the Description page of Project Settings.

#include "SimplyInputSettingsSaveGame.h"
#include "EnhancedInputLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"

void USimplyInputSettingsSaveGame::LoadInputMappingsToSaveGame()
{
    SavedInputMappings.Empty();
    const USimplyConfigSettings *SimplySettings = GetDefault<USimplyConfigSettings>();

    for (UInputMappingContext *C : SimplySettings->Contexts.Contexts)
    {
        FSimplySavedInputSettings Saved = FSimplySavedInputSettings();
        Saved.Context = C;
        Saved.Mappings = C->GetMappings();
        SavedInputMappings.Add(Saved);
    }
}

FAudioSetting USimplyInputSettingsSaveGame::GetVolumeSetting(USoundMix *InSoundMix, USoundClass *InAudioClass)
{
    if (!AudioSettings.IsEmpty())
    {
        for (FAudioSetting S : AudioSettings)
        {
            if (S.AudioClass == InAudioClass && S.SoundMix && InSoundMix)
            {
                return S;
            }
        }
    }
    return FAudioSetting(InSoundMix, InAudioClass);
}

void USimplyInputSettingsSaveGame::SetVolumeSetting(USoundMix *InSoundMix, USoundClass *InAudioClass, float InVolume)
{
    if (AudioSettings.Num() > 0)
    {
        const bool AlreadyExists = AudioSettings.ContainsByPredicate([InSoundMix, InAudioClass](FAudioSetting &S)
                                                                     { return S.SoundMix == InSoundMix && S.AudioClass == InAudioClass; });

        if (AlreadyExists)
        {
            for (FAudioSetting &S : AudioSettings)
            {
                if (S.AudioClass == InAudioClass && S.SoundMix && InSoundMix)
                {
                    S.Volume = InVolume;
                }
            }
        }
        else
        {
            AudioSettings.Add(FAudioSetting(InSoundMix, InAudioClass, InVolume));
        }
    }
}

void USimplyInputSettingsSaveGame::SetPitchSetting(USoundMix *InSoundMix, USoundClass *InAudioClass, float InPitch)
{
    const bool AlreadyExists = AudioSettings.ContainsByPredicate([InSoundMix, InAudioClass](FAudioSetting &S)
                                                                 { return S.SoundMix == InSoundMix && S.AudioClass == InAudioClass; });

    if (AlreadyExists)
    {
        for (FAudioSetting &S : AudioSettings)
        {
            if (S.AudioClass == InAudioClass && S.SoundMix && InSoundMix)
            {
                S.Pitch = InPitch;
            }
        }
    }
    else
    {
        FAudioSetting Setting = FAudioSetting(InSoundMix, InAudioClass);
        Setting.Pitch = InPitch;
        AudioSettings.Add(Setting);
    }
}

void USimplyInputSettingsSaveGame::ApplySimplySettingsAudio(UObject *WorldContextObject)
{
    const UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
    USimplyInputSettingsSaveGame *Settings = USimplyConfigSettings::GetCachedSettings();
    if (!World || !Settings)
    {
        return;
    }

    for (const FAudioSetting Setting : Settings->AudioSettings)
    {
        if (Setting.SoundMix && Setting.AudioClass)
        {
            UGameplayStatics::SetSoundMixClassOverride(World, Setting.SoundMix, Setting.AudioClass, Setting.Volume,
                                                       Setting.Pitch, 0);
            UGameplayStatics::PushSoundMixModifier(World, Setting.SoundMix);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Simply Settings contains a bad sound setting configuration"));
        }
    }
}

FString USimplyInputSettingsSaveGame::GetCustomSimplySetting(FString SettingKey)
{
    USimplyInputSettingsSaveGame *CurrentSettings = USimplyConfigSettings::GetCachedSettings();
    if (SettingKey.IsEmpty() || !CurrentSettings || CurrentSettings->CustomSettings.IsEmpty())
    {
        return "";
    }
    return *CurrentSettings->CustomSettings.Find(SettingKey);
}

int USimplyInputSettingsSaveGame::GetCustomSettingsAsInt(FString SettingKey)
{
    return UKismetStringLibrary::Conv_StringToInt(GetCustomSimplySetting(SettingKey));
}

int USimplyInputSettingsSaveGame::GetCustomSettingsAsFloat(FString SettingKey)
{
    return FCString::Atof(*GetCustomSimplySetting(SettingKey));
}

bool USimplyInputSettingsSaveGame::GetCustomSettingsAsBool(FString SettingKey)
{
    return GetCustomSimplySetting(SettingKey).Equals("True");
}

void USimplyInputSettingsSaveGame::SetCustomSettings(FString SettingKey, FString Value)
{
    USimplyInputSettingsSaveGame *CurrentSettings = USimplyConfigSettings::GetCachedSettings();
    if (CurrentSettings)
    {
        CurrentSettings->CustomSettings.Add(SettingKey, Value);

        USimplyConfigSettings *SimplySettings = GetMutableDefault<USimplyConfigSettings>();
        if (SimplySettings->SimplySettingsChangedDelegate.IsBound())
        {
            SimplySettings->SimplySettingsChangedDelegate.Broadcast();
        }
    }
}

void USimplyInputSettingsSaveGame::ApplySimplyInputSettings(UObject *WorldContextObject)
{
    USimplyInputSettingsSaveGame *CurrentSaveGame = Cast<USimplyInputSettingsSaveGame>(UGameplayStatics::LoadGameFromSlot(USimplyConfigSettings::SaveGameName, 0));

    if (!CurrentSaveGame)
    {
        return;
    }

    for (FSimplySavedInputSettings SavedInput : CurrentSaveGame->SavedInputMappings)
    {

        for (FEnhancedActionKeyMapping Mapping : SavedInput.Mappings)
        {

            int Index = SavedInput.Context->GetMappings().IndexOfByPredicate([Mapping](FEnhancedActionKeyMapping M)
                                                                             {
																	bool result = Mapping.Action == M.Action;
														if((M.GetPlayerMappableKeySettings() && !Mapping.GetPlayerMappableKeySettings()) || (!M.GetPlayerMappableKeySettings() && Mapping.GetPlayerMappableKeySettings()))		{
															return false;
														}	
				if(M.GetPlayerMappableKeySettings()){
					result =  Mapping.GetPlayerMappableKeySettings()->Name==M.GetPlayerMappableKeySettings()->Name;
				}
				return result; });

            if (Index >= 0)
            {
                SavedInput.Context->GetMapping(Index).Key = Mapping.Key;
            }
        }
        UEnhancedInputLibrary::RequestRebuildControlMappingsUsingContext(SavedInput.Context);
    }
}
