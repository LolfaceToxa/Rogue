// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseSimplyWindow.h"
#include "SimplyInfoWindow.generated.h"

UCLASS()
class SIMPLYWINDOW_API USimplyInfoWindow : public UBaseSimplyWindow
{
	GENERATED_BODY()

public:
	FSimplyWindowConfirmDelegate ConfirmDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category="SimplyWindow")
	class UTextBlock* InfoText;

	UFUNCTION(BlueprintCallable, Category="SimplyConfirmationWindow")
	virtual void Confirm();
};
