// Copyright Phoinix-DEV

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InputMappingContext.h"
#include "Components/BoxComponent.h"
#include "Components/Button.h"
#include "InputSettingsWidget.generated.h"

struct FInputActionKeyMapping;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRefresh);

UCLASS()
class SIMPLYSETTINGS_API UInputSettingsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

};
