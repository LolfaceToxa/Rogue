// Copyright Phoinix-DEV


#include "SimplySettings_Button.h"
#include "SimplyConfigSettings.h"
#include "Blueprint/WidgetTree.h"

USimplySettings_Button::USimplySettings_Button()
{
}

void USimplySettings_Button::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	USimplyConfigSettings* SimplySettings = GetMutableDefault<USimplyConfigSettings>();

	if (!OnClicked.IsAlreadyBound(this, &USimplySettings_Button::HandleClick))
	{
		OnClicked.AddDynamic(this, &USimplySettings_Button::HandleClick);
	}

	if (!SimplySettings->SimplySettingsChangedDelegate.IsBoundToObject(this))
	{
		SimplySettings->SimplySettingsChangedDelegate.AddUObject(this, &USimplySettings_Button::RefreshColor);
	}

	DefaultStyle = GetStyle();

	RefreshColor();
}

void USimplySettings_Button::HandleClick()
{
	OnClick();
	const USimplyConfigSettings* SimplySettings = GetMutableDefault<USimplyConfigSettings>();
	if (SimplySettings->SimplySettingsChangedDelegate.IsBound())
	{
		SimplySettings->SimplySettingsChangedDelegate.Broadcast();
	}

}

void USimplySettings_Button::OnClick_Implementation()
{
	if (ExecuteCV)
	{
		FString Command = CVar.Append(" ");
		Command = Command.Append(RepresentedValue);
		GEngine->Exec(GetWorld(), *Command);
	}
}

void USimplySettings_Button::RefreshColor()
{
	if (IsActive())
	{
		SetStyle(ActiveStyle);
	}
	else
	{
		SetStyle(DefaultStyle);
	}
}

bool USimplySettings_Button::IsActive_Implementation()
{
	if (ExecuteCV)
	{
		FStringOutputDevice Output;
		GEngine->Exec(GetWorld(), *CVar, Output);

		const int Start = Output.Find("\"", ESearchCase::IgnoreCase, ESearchDir::FromStart);
		const int End = Output.Find("\"", ESearchCase::IgnoreCase, ESearchDir::FromEnd) - Start + 1;

		FString Result = Output.Mid(Start, End);
		Result.TrimQuotesInline();

		return RepresentedValue.Equals(Result);
	}
	return false;
}
