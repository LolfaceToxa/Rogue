// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SimplyWindowManager.generated.h"

UCLASS()
class SIMPLYWINDOW_API USimplyWindowManager : public UUserWidget
{
	GENERATED_BODY()

public:
	// The Z-Order of the Windows
	UPROPERTY(BlueprintReadOnly,  Category="Setup")
	int SimplyWindowsZOrder = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category="SimpyWindow")
	class UCanvasPanel* MainPanel;

	void SetHighestPriority(class UBaseSimplyWindow* Window) const;
};
