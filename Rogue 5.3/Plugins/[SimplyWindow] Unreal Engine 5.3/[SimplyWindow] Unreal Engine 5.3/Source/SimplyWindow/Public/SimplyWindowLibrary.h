// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SimplyWindowLibrary.generated.h"

class UBaseSimplyWindow;

UCLASS()
class SIMPLYWINDOW_API USimplyWindowLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Creates a SimplyWindow and adds it to the viewport. Returns a SimplyWindow, you may want to set the position on it.
	// Draggable has only an effect, if the given WindowClass is draggable.
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "World", AdvancedDisplay="Draggable"),  Category="SimplyWindow")
	static UBaseSimplyWindow* CreateSimplyWindow(UObject* World, TSubclassOf<UBaseSimplyWindow> WindowClass,
	                                             TSubclassOf<UUserWidget> ContentClass,
	                                             FVector2D Size = FVector2D(0, 0), bool Draggable = true);

	// Creates a Window and adds it to the Viewport. It adds only the given Window and injects no Content.
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "World", AdvancedDisplay="Draggable"),  Category="SimplyWindow")
	static UBaseSimplyWindow* CreatCompactWindow(UObject* World, TSubclassOf<UBaseSimplyWindow> WindowClass,
	                                             FVector2D Size = FVector2D(0, 0), bool Draggable = true);

	/**
	 * Positions Utility Methods
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "World"), Category="SimplyWindow")
	static FVector2D GetRelativeViewportTopCenter(UObject* World, UBaseSimplyWindow* Widget);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "World"), Category="SimplyWindow")
	static FVector2D GetRelativeViewportTopRight(UObject* World, UBaseSimplyWindow* Widget);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "World"), Category="SimplyWindow")
	static FVector2D GetRelativeViewportMiddleLeft(UObject* World, UBaseSimplyWindow* Widget);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "World"), Category="SimplyWindow")
	static FVector2D GetRelativeViewportMiddleCenter(UObject* World, UBaseSimplyWindow* Widget);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "World"), Category="SimplyWindow")
	static FVector2D GetRelativeViewportMiddleRight(UObject* World, UBaseSimplyWindow* Widget);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "World"), Category="SimplyWindow")
	static FVector2D GetRelativeViewportBottomLeft(UObject* World, UBaseSimplyWindow* Widget);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "World"), Category="SimplyWindow")
	static FVector2D GetRelativeViewportBottomCenter(UObject* World, UBaseSimplyWindow* Widget);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "World"), Category="SimplyWindow")
	static FVector2D GetRelativeViewportBottomRight(UObject* World, UBaseSimplyWindow* Widget);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "World"), Category="SimplyWindow")
	static FVector2D GetDPIScaledViewport(UObject* World);
};
