// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimplyWindowManager.h"
#include "Blueprint/UserWidget.h"
#include "BaseSimplyWindow.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSimplyWindowResponse);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSimplyWindowConfirmDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSimplyWindowAbortDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSimplyWindowCreateDelegate, UObject*, Window);

UENUM(BlueprintType)
enum ESimplyWindowPosition
{
	None,
	TopLeft,
	TopCenter,
	TopRight,
	MiddleLeft,
	MiddleCenter,
	MiddleRight,
	BottomLeft,
	BottomCenter,
	BottomRight
};

UCLASS()
class SIMPLYWINDOW_API UBaseSimplyWindow : public UUserWidget
{
	GENERATED_BODY()

public:
	// Whether the Window can be dragged or not
	UPROPERTY(BlueprintReadWrite, Category="SimplyWidget")
	bool bDraggable = true;

	// If checked, this property ensures that the window can't be dragged out of the Main Game Window
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Security")
	bool bActivateSecurityBorders;

	// The security Border for the Min Values (X/Y)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Security",
		meta=(EditCondition="bActivateSecurityBorders"))
	FVector2D SecurityBorderMin = FVector2D(10, 10);

	// The security Border for the Max Values (X/Y)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Security",
		meta=(EditCondition="bActivateSecurityBorders"))
	FVector2D SecurityBorderMax = FVector2D(10, 10);

	// If checked, this property ensures a Minimum Size of the Window, only relevant if resizable
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Security")
	bool bActiveMinWindowSize = true;

	// The Minimum WindowSize
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Security",
		meta=(EditCondition="bActiveMinWindowSize"))
	FVector2D MinWindowSize = FVector2D(100, 100);

	// If checked, this property ensures a Maximum Size of the Window, only relevant if resizable
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Security")
	bool bActiveMaxWindowSize = false;

	// The Maximum WindowSize
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Security",
		meta=(EditCondition="bActiveMaxWindowSize"))
	FVector2D MaxWindowSize = FVector2D(800, 1000);

	UPROPERTY(EditDefaultsOnly, Category="Security")
	TSubclassOf<class USimplyWindowManager> Manager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category="SimplyWindow")
	class UCanvasPanel* Window;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category="SimplyWindow")
	class UButton* TopBar;

	UPROPERTY(BlueprintReadOnly, Category="SimplyWindow")
	UUserWidget* WindowContent;

	UBaseSimplyWindow(const FObjectInitializer& ObjectInitializer);

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="SimplyWindow")
	USimplyWindowManager* GetWindowManager();

	UFUNCTION(BlueprintCallable, Category="SimplyWindow")
	virtual void InitializeWindow(TSubclassOf<UUserWidget> Content = nullptr);

	UFUNCTION(BlueprintCallable, Category="SimplyWindow")
	void SetSize(FVector2D Size);

	UFUNCTION(BlueprintCallable, Category="SimplyWindow")
	virtual void StartDrag();

	UFUNCTION(BlueprintCallable, Category="SimplyWindow")
	virtual void StopDrag();

	UFUNCTION(BlueprintCallable, Category="SimplyWindow")
	virtual void StartResizing();

	UFUNCTION(BlueprintCallable, Category="SimplyWindow")
	virtual void StopResizing();

	UFUNCTION(BlueprintCallable, Category="SimplyWindow")
	virtual void CloseWindow();

	UFUNCTION(BlueprintCallable, Category="SimplyWindow")
	virtual void HideWindow();

	UFUNCTION(BlueprintCallable, Category="SimplyWindow")
	virtual void UnHideWindow();

	UFUNCTION(BlueprintCallable, Category="SimplyWindow")
	virtual void SetLocked(bool Locked);

	UFUNCTION(BlueprintCallable, Category="SimplyWindow")
	virtual void SwitchLockedState();

	UFUNCTION(BlueprintCallable, Category="SimplyWindow")
	virtual bool IsLocked() const;

	UFUNCTION(BlueprintCallable, Category="SimplyWindow")
	FVector2D GetBodyRelativeOffset(FVector2D PositionToMakeRelative) const;

	/**
	 * Position Methods
	 */
	UFUNCTION(BlueprintCallable, Category="SimplyWindow")
	void SetSimplyWindowPositionDirectly(FVector2D Position);

	UFUNCTION(BlueprintCallable, Category="SimplyWindow")
	void SetSimplyWindowPosition(ESimplyWindowPosition Position);

protected:
	UPROPERTY(BlueprintReadOnly, Category="SimplyWindow")
	bool bIsDragging;

	UPROPERTY(BlueprintReadOnly, Category="SimplyWindow")
	bool bIsResizing;

private:
	FVector2D DragOffset;
	FVector2D ResizingOffset;

	bool bLocked;
};
