// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseSimplyWindow.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CreateSimplyConfirmationWindow.generated.h"

class USimplyConfirmationWindow;

UCLASS()
class SIMPLYWINDOW_API UCreateSimplyConfirmationWindow : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category="SimplyWindow")
	FSimplyWindowCreateDelegate OnWindowCreated;

	UPROPERTY(BlueprintAssignable, Category="SimplyWindow")
	FSimplyWindowResponse OnConfirm;

	UPROPERTY(BlueprintAssignable)
	FSimplyWindowResponse OnAbort;

	TSubclassOf<USimplyConfirmationWindow> WindowClass;

	UPROPERTY()
	USimplyConfirmationWindow* SimplyWindow;

	FText ConfirmationText;
	bool bDraggable;
	FVector2D TargetPosition;

	UFUNCTION(BlueprintCallable,
		meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", AdvancedDisplay=
			"Draggable, Position"),
		Category = "SimplyWindow")
	static UCreateSimplyConfirmationWindow* CreateSimplyConfirmationWindow(
		const UObject* WorldContextObject,
		TSubclassOf<USimplyConfirmationWindow> ConfirmationWindow,
		FText Text,
		FVector2D Position = FVector2D(0, 0),
		bool Draggable = true);

	virtual void Activate() override;

private:
	const UObject* WorldContextObject;

	UFUNCTION()
	void Confirm();

	UFUNCTION()
	void Abort();
};
