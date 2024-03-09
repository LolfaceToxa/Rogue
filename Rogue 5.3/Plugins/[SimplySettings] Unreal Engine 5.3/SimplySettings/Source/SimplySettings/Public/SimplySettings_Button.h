// Copyright Phoinix-DEV

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "SimplySettings_Button.generated.h"

UCLASS()
class SIMPLYSETTINGS_API USimplySettings_Button : public UButton
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Setup")
	FButtonStyle ActiveStyle;

	// This is the value that this component represents e.g. 2
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	FString RepresentedValue = "0";

	/**
	 * You can execute CVar by checking this Option. Just specify the CVar and Value
	 * The IsActive will return true if the CVar Values matches the Represented Value.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	bool ExecuteCV = false;

	UPROPERTY(EditAnywhere, Category="Setup", meta=(EditCondition="ExecuteCV"))
	FString CVar = "";

	USimplySettings_Button();

	virtual void OnWidgetRebuilt() override;

	UFUNCTION()
	void HandleClick();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Simply Settings")
	void OnClick();

	UFUNCTION(BlueprintCallable, Category="Simply Settings")
	virtual void RefreshColor();

	// Whether the represented Setting is currently active
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Simply Settings")
	bool IsActive();

private:
	FButtonStyle DefaultStyle;
};
