// Copyright Phoinix-DEV

#pragma once

#include "CoreMinimal.h"
#include "Components/ComboBoxString.h"
#include "SimplySettings_ComboBoxString.generated.h"

UCLASS()
class SIMPLYSETTINGS_API USimplySettings_ComboBoxString : public UComboBoxString
{
	GENERATED_BODY()

public:
	/** Differentiate between automatic assignment and manual one
	* This is required as there should be no userfeedback in the auto mode
	*/
	UPROPERTY(BlueprintReadWrite, Category="Simply Settings")
	bool ManualMode = true;

	virtual void OnWidgetRebuilt() override;

	UFUNCTION()
	void HandleSelect(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION(BlueprintImplementableEvent)
	void InitializeOptions();

	UFUNCTION(BlueprintImplementableEvent)
	void OnSelect(FName SelectedItem, ESelectInfo::Type SelectionType);
};
