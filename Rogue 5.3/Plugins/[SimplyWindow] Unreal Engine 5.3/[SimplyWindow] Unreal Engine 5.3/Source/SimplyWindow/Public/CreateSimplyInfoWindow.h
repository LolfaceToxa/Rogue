// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseSimplyWindow.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CreateSimplyInfoWindow.generated.h"

class USimplyInfoWindow;
UCLASS()
class SIMPLYWINDOW_API UCreateSimplyInfoWindow : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FSimplyWindowCreateDelegate OnWindowCreated;

	UPROPERTY(BlueprintAssignable)
	FSimplyWindowResponse OnConfirm;

	TSubclassOf<USimplyInfoWindow> WindowClass;

	UPROPERTY()
	USimplyInfoWindow* SimplyWindow;

	FText InfoText;
	bool bDraggable;
	FVector2D TargetPosition;

	UFUNCTION(BlueprintCallable,
		meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", AdvancedDisplay=
			"Draggable, Position"),
		Category = "SimplWindow")
	static UCreateSimplyInfoWindow* CreateSimplyInfoWindow(
		const UObject* WorldContextObject,
		TSubclassOf<USimplyInfoWindow> InfoWindow,
		FText Text,
		FVector2D Position = FVector2D(0, 0),
		bool Draggable = true);

	virtual void Activate() override;

private:
	const UObject* WorldContextObject;

	UFUNCTION()
	void Confirm();
};
