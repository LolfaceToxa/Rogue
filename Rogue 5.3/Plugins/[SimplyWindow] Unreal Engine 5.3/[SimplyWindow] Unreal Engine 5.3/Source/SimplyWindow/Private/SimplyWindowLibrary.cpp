// Fill out your copyright notice in the Description page of Project Settings.


#include "SimplyWindowLibrary.h"
#include "BaseSimplyWindow.h"
#include "SimplyWindowManager.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

UBaseSimplyWindow* USimplyWindowLibrary::CreateSimplyWindow(UObject* World,
                                                            TSubclassOf<UBaseSimplyWindow> WindowClass,
                                                            TSubclassOf<UUserWidget> ContentClass,
                                                            FVector2D Size,
                                                            bool Draggable)
{
	UBaseSimplyWindow* SimplyWindow = CreateWidget<UBaseSimplyWindow>(World->GetWorld()->GetFirstPlayerController(),
	                                                                  WindowClass);

	SimplyWindow->GetWindowManager()->MainPanel->AddChild(SimplyWindow);
	SimplyWindow->InitializeWindow(ContentClass);
	if (Size.Size() > 0)
	{
		SimplyWindow->SetSize(Size);
	}
	SimplyWindow->bDraggable = Draggable;
	return SimplyWindow;
}

UBaseSimplyWindow* USimplyWindowLibrary::CreatCompactWindow(UObject* World, TSubclassOf<UBaseSimplyWindow> WindowClass,
                                                            FVector2D Size, bool Draggable)
{
	return CreateSimplyWindow(World, WindowClass, nullptr, Size, Draggable);
}

FVector2D USimplyWindowLibrary::GetRelativeViewportTopCenter(UObject* World, UBaseSimplyWindow* Widget)
{
	UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(Widget->Window->Slot);
	FVector2D TargetLocation;
	if (CanvasPanelSlot)
	{
		TargetLocation = GetDPIScaledViewport(World) / 2;
		TargetLocation = TargetLocation - CanvasPanelSlot->GetSize() / 2;
		TargetLocation.Y = 0;
	}
	return TargetLocation;
}

FVector2D USimplyWindowLibrary::GetRelativeViewportTopRight(UObject* World, UBaseSimplyWindow* Widget)
{
	UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(Widget->Window->Slot);
	FVector2D TargetLocation;
	if (CanvasPanelSlot)
	{
		TargetLocation = GetDPIScaledViewport(World);
		TargetLocation = TargetLocation - CanvasPanelSlot->GetSize();
		TargetLocation.Y = 0;
	}
	return TargetLocation;
}

FVector2D USimplyWindowLibrary::GetRelativeViewportMiddleLeft(UObject* World, UBaseSimplyWindow* Widget)
{
	UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(Widget->Window->Slot);
	FVector2D TargetLocation;
	if (CanvasPanelSlot)
	{
		TargetLocation = GetDPIScaledViewport(World) / 2;
		TargetLocation = TargetLocation - (CanvasPanelSlot->GetSize() / 2);
		TargetLocation.X = 0;
	}
	return TargetLocation;
}

FVector2D USimplyWindowLibrary::GetRelativeViewportMiddleCenter(UObject* World, UBaseSimplyWindow* Widget)
{
	UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(Widget->Window->Slot);
	FVector2D TargetLocation;
	if (CanvasPanelSlot)
	{
		TargetLocation = GetDPIScaledViewport(World) / 2;
		TargetLocation = TargetLocation - (CanvasPanelSlot->GetSize() / 2);
	}
	return TargetLocation;
}

FVector2D USimplyWindowLibrary::GetRelativeViewportMiddleRight(UObject* World, UBaseSimplyWindow* Widget)
{
	UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(Widget->Window->Slot);
	FVector2D TargetLocation;
	if (CanvasPanelSlot)
	{
		TargetLocation.X = GetDPIScaledViewport(World).X;
		TargetLocation.Y = GetDPIScaledViewport(World).Y / 2;
		TargetLocation.Y = TargetLocation.Y - (CanvasPanelSlot->GetSize().Y / 2);
		TargetLocation.X = TargetLocation.X - (CanvasPanelSlot->GetSize().X);
	}
	return TargetLocation;
}

FVector2D USimplyWindowLibrary::GetRelativeViewportBottomLeft(UObject* World, UBaseSimplyWindow* Widget)
{
	UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(Widget->Window->Slot);
	FVector2D TargetLocation;
	if (CanvasPanelSlot)
	{
		TargetLocation = GetDPIScaledViewport(World);
		TargetLocation.Y = TargetLocation.Y - CanvasPanelSlot->GetSize().Y;
		TargetLocation.X = 0;
	}
	return TargetLocation;
}

FVector2D USimplyWindowLibrary::GetRelativeViewportBottomCenter(UObject* World, UBaseSimplyWindow* Widget)
{
	UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(Widget->Window->Slot);
	FVector2D TargetLocation;
	if (CanvasPanelSlot)
	{
		TargetLocation = GetDPIScaledViewport(World) / 2;
		TargetLocation.X = TargetLocation.X - (CanvasPanelSlot->GetSize().X / 2);
		TargetLocation.Y = GetDPIScaledViewport(World).Y - CanvasPanelSlot->GetSize().Y;
	}
	return TargetLocation;
}

FVector2D USimplyWindowLibrary::GetRelativeViewportBottomRight(UObject* World, UBaseSimplyWindow* Widget)
{
	UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(Widget->Window->Slot);
	FVector2D TargetLocation;
	if (CanvasPanelSlot)
	{
		TargetLocation = GetDPIScaledViewport(World);
		TargetLocation = TargetLocation - CanvasPanelSlot->GetSize();
	}
	return TargetLocation;
}

FVector2D USimplyWindowLibrary::GetDPIScaledViewport(UObject* World)
{
	const float DPI = 1 / UWidgetLayoutLibrary::GetViewportScale(World);
	return UWidgetLayoutLibrary::GetViewportSize(World) * DPI;
}
