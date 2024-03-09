// Copyright Phoinix-DEV

#include "InputSettingsWidget.h"
#include "Kismet/GameplayStatics.h"
#include "SimplyConfigSettings.h"
#include "EnhancedInputLibrary.h"
#include "Components/ScrollBox.h"
#include "Engine/World.h"
#include "SimplySettings_InputScrollBox.h"
#include "SimplyInputSettingsSaveGame.h"
#include "SimplySettings_KeySelector.h"

void UInputSettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TArray<UWidget *> Children;
	WidgetTree->GetAllWidgets(Children);

	for (UWidget *Child : Children)
	{
		if (Child->IsA(USimplySettings_InputScrollBox::StaticClass()))
		{
			USimplySettings_InputScrollBox *ScrollBox = Cast<USimplySettings_InputScrollBox>(Child);
			ScrollBox->ExecuteAutoGenerate();
		}
	}

}
