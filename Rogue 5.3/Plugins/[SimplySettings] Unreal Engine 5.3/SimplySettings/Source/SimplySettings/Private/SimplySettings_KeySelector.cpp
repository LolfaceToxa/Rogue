// Copyright Phoinix-DEV

#include "SimplySettings_KeySelector.h"
#include "EnhancedInputLibrary.h"
#include "GameFramework/InputSettings.h"
#include "PlayerMappableKeySettings.h"
#include "CtrlInputTrigger.h"
#include "SimplyConfigSettings.h"

void USimplySettings_KeySelector::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	USimplyConfigSettings *SimplySettings = GetMutableDefault<USimplyConfigSettings>();
	InitializeMapping();

	// We need to refresh when the setup changes
	if (SimplySettings && !SimplySettings->SimplySettingsChangedDelegate.IsBoundToObject(
							  this))
	{
		SimplySettings->SimplySettingsChangedDelegate.AddUObject(this, &USimplySettings_KeySelector::InitializeMapping);
	}

	if (!OnKeySelected.IsAlreadyBound(this, &USimplySettings_KeySelector::HandleNewKeySelected))
	{
		OnKeySelected.AddDynamic(this, &USimplySettings_KeySelector::HandleNewKeySelected);
	}
}

void USimplySettings_KeySelector::InitializeSelector(UInputAction *InInputAction, UInputMappingContext *InContext, FName InMappingName)
{
	if (InContext)
	{
		Context = InContext;
	}
	if (InInputAction)
	{
		InputAction = InInputAction;
	}
	MappingName = InMappingName;
}

void USimplySettings_KeySelector::InitializeMapping()
{
	FInputChord Key;

	if (!Context || !InputAction)
	{
		SetIsEnabled(false);
	}
	else
	{

		TArray<FEnhancedActionKeyMapping> Mappings = Context->GetMappings().FilterByPredicate([this](const FEnhancedActionKeyMapping Element)
																							  { return Element.Action.Get() == InputAction; });

		if (Mappings.Num() > 1)
		{
			Mappings = Mappings.FilterByPredicate([this](FEnhancedActionKeyMapping Element)
												  {
				if (Element.GetPlayerMappableKeySettings())
				{
					return Element.GetPlayerMappableKeySettings()->Name.IsEqual(MappingName);
				}
				return false; });
		}

		if (Mappings.Num() > 0)
		{
			SetIsEnabled(true);
			Key.Key = Mappings[0].Key;
		}
		else
		{
			SetIsEnabled(false);
		}

		ManualMode = false;
		SetSelectedKey(Key);
		ManualMode = true;
	}
}

bool USimplySettings_KeySelector::SelectKey(FInputChord Key)
{
	if (!ensure(Context))
	{
		return false;
	}

	// Check whether key is blacklisted
	USimplyConfigSettings *SimplySettings = GetMutableDefault<USimplyConfigSettings>();
	if (SimplySettings->KeyBlacklist.Contains(Key))
	{
		InitializeMapping();
		OnBlacklistedKeySelected(GetWorld(), Key, Key);
		return false;
	}

	// Not blacklisted, lets get the index of the mapping to modify
	int Index = Context->GetMappings().IndexOfByPredicate([this](FEnhancedActionKeyMapping Mapping)
														  {
															if(Mapping.GetPlayerMappableKeySettings()){
																if(!MappingName.IsNone()){
																	 return Mapping.Action == InputAction && Mapping.GetPlayerMappableKeySettings()->Name.IsEqual(MappingName);
																}
															UE_LOG(LogTemp, Warning, TEXT("SimplySettings: Some Mappings do not have Player Mappable Key Settings, this might cause wrong Mappings."))
															return Mapping.Action == InputAction;
															} 
															return false; });

	// If multibinding is not allowed, we need to check all the other mappings as well
	if (!SimplySettings->AllowMultiBinding)
	{
		TArray<FSimplySettingsContexts> UniqueContextGroups = SimplySettings->UniqueContextGroups.FilterByPredicate([this](const FSimplySettingsContexts UniqueContextGroup)
																													{ return UniqueContextGroup.Contexts.Contains(Context); });

		for (FSimplySettingsContexts UniqueContextGroup : UniqueContextGroups)
		{
			for (UInputMappingContext *M : UniqueContextGroup.Contexts)
			{
				for (FEnhancedActionKeyMapping *Mapping : GetMatchingMappingsFromContext(Key, M))
				{
					Mapping->Key = FKey();
				}
			}
		}
	}

	if (Index >= 0)
	{

		FEnhancedActionKeyMapping &Mapping = Context->GetMapping(Index);
		Mapping.Key = Key.Key;
	}

	InitializeMapping();
	SimplySettings->SimplySettingsChangedDelegate.Broadcast();

	return true;
}

bool USimplySettings_KeySelector::IsKeyAlreadyBound(FInputChord Key)
{
	USimplyConfigSettings *SimplySettings = GetMutableDefault<USimplyConfigSettings>();
	TArray<FSimplySettingsContexts> Groups = SimplySettings->UniqueContextGroups.FilterByPredicate([this](FSimplySettingsContexts Group)
																								   { return Group.Contexts.Contains(Context); });

	for (FSimplySettingsContexts Group : Groups)
	{
		for (UInputMappingContext *CurrentContext : Group.Contexts)
		{
			if (GetMatchingMappingsFromContext(Key, CurrentContext).Num() > 0)
			{
				return true;
			}
		}
	}
	return false;
}

TArray<FEnhancedActionKeyMapping *> USimplySettings_KeySelector::GetMatchingMappingsFromContext(const FInputChord NewSelectedKey, UInputMappingContext *InContext)
{
	TArray<FEnhancedActionKeyMapping *> Mappings;

	for (int i = 0; i < InContext->GetMappings().Num(); i++)
	{
		FEnhancedActionKeyMapping &CurrentMapping = InContext->GetMapping(i);
		TArray<UClass *> TriggerClasses;
		for (UInputTrigger *Trigger : CurrentMapping.Triggers)
		{
			if (Trigger)
			{
				TriggerClasses.Add(Trigger->GetClass());
			}
		}

		if (InContext->GetMappings()[i].Key == NewSelectedKey.Key)
		{
			Mappings.Add(&CurrentMapping);
		}
	}
	return Mappings;
}

void USimplySettings_KeySelector::HandleNewKeySelected(FInputChord NewKey)
{
	if (ManualMode)
	{
		OnNewKeySelected(NewKey);
	}
}