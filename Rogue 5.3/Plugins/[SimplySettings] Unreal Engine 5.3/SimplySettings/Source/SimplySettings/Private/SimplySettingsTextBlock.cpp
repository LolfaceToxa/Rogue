// Copyright Phoinix-DEV

#include "SimplySettingsTextBlock.h"
#include "EnhancedActionKeyMapping.h"

void USimplySettingsTextBlock::OnWidgetRebuilt()
{
    Super::OnWidgetRebuilt();
    Refresh();
}

void USimplySettingsTextBlock::Refresh()
{
    if (Context != nullptr && InputAction != nullptr)
    {
        TArray<FEnhancedActionKeyMapping> Mappings = Context->GetMappings().FilterByPredicate([this](const FEnhancedActionKeyMapping &Element)
                                                                                              { return Element.Action == InputAction; });

        if (Mappings.Num() > 1)
        {
            Mappings = Mappings.FilterByPredicate([this](const FEnhancedActionKeyMapping &Element)
                                                  {
                if (Element.GetPlayerMappableKeySettings())
                {
                    return Element.GetPlayerMappableKeySettings()->Name == MappingName;
                }
                return false; });
        }
        if (Mappings.Num() > 0 && Mappings[0].GetPlayerMappableKeySettings())
        {
            SetText(Mappings[0].GetPlayerMappableKeySettings()->DisplayName);
        }
    }
}

void USimplySettingsTextBlock::InitializeLabel(UInputMappingContext *InContext, UInputAction *InInputAction, FName InMappingName)
{
    this->Context = InContext;
    this->InputAction = InInputAction;
    this->MappingName = InMappingName;
    this->Refresh();
}