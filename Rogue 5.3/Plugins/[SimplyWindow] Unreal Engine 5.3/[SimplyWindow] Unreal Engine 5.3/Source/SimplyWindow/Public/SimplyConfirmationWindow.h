// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseSimplyWindow.h"
#include "SimplyConfirmationWindow.generated.h"

class UTextBlock;

UCLASS()
class SIMPLYWINDOW_API USimplyConfirmationWindow : public UBaseSimplyWindow
{
	GENERATED_BODY()

public:
	FSimplyWindowConfirmDelegate ConfirmDelegate;
	FSimplyWindowAbortDelegate AbortDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category="SimplyWindow")
	UTextBlock* ConfirmationText;

	virtual void HideWindow() override;
	virtual void CloseWindow() override;

	UFUNCTION(BlueprintCallable, Category="SimplyConfirmationWindow")
	virtual void Confirm();
};
