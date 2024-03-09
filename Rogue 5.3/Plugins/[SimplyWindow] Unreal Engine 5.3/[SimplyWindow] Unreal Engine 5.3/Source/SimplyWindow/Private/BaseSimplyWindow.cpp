// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSimplyWindow.h"
#include "UObject/ConstructorHelpers.h"
#include "SimplyWindowLibrary.h"
#include "SimplyWindowManager.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

UBaseSimplyWindow::UBaseSimplyWindow(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	const ConstructorHelpers::FClassFinder<USimplyWindowManager> ManagerClass(
		TEXT("/SimplyWindow/Core/WP_SimplyWindowManager"));
	Manager = ManagerClass.Class;
}

void UBaseSimplyWindow::InitializeWindow(TSubclassOf<UUserWidget> Content)
{
	ensure(Manager);

	if (Content)
	{
		WindowContent = CreateWidget<UUserWidget>(this, Content);
		UPanelSlot* WindowPanelSlot = Window->AddChild(WindowContent);

		const UCanvasPanelSlot* TopBarSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(TopBar);
		UCanvasPanelSlot* WindowCanvasPanelSlot = Cast<UCanvasPanelSlot>(WindowPanelSlot);

		if (WindowCanvasPanelSlot)
		{
			WindowCanvasPanelSlot->SetAnchors(FAnchors(0, 0, 1, 1));
			WindowCanvasPanelSlot->SetOffsets(FMargin(0, TopBarSlot->GetSize().Y, 0, 0));
		}
	}

	GetWindowManager()->SetHighestPriority(this);
}

void UBaseSimplyWindow::SetSize(FVector2D Size)
{
	UCanvasPanelSlot* WindowSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(Window);
	WindowSlot->SetSize(Size);

	if (bActiveMinWindowSize && (Size.X < MinWindowSize.X || Size.Y < MinWindowSize.Y))
	{
		WindowSlot->SetSize(MinWindowSize);
	}

	if (bActiveMaxWindowSize && (Size.X > MaxWindowSize.X || Size.Y > MaxWindowSize.Y))
	{
		WindowSlot->SetSize(MaxWindowSize);
	}
}

void UBaseSimplyWindow::StartDrag()
{
	if (bDraggable)
	{
		const FVector2D MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
		DragOffset = GetBodyRelativeOffset(MousePosition);
		bIsDragging = true;
		GetWindowManager()->SetHighestPriority(this);
	}
}

void UBaseSimplyWindow::StopDrag()
{
	bIsDragging = false;
	if (bActivateSecurityBorders)
	{
		UCanvasPanelSlot* WindowSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(Window);
		FVector2D CurrentPosition = WindowSlot->GetPosition();
		const FVector2D ViewPortScaled = UWidgetLayoutLibrary::GetViewportSize(GetWorld()) * (1 /
			UWidgetLayoutLibrary::GetViewportScale(GetWorld()));

		if (CurrentPosition.X < SecurityBorderMin.X)
		{
			CurrentPosition.X = SecurityBorderMin.X;
		}
		else if (CurrentPosition.X > ViewPortScaled.X - SecurityBorderMax.X)
		{
			CurrentPosition.X = ViewPortScaled.X - SecurityBorderMax.X;
		}

		if (CurrentPosition.Y < SecurityBorderMin.Y)
		{
			CurrentPosition.Y = SecurityBorderMin.Y;
		}
		else if (CurrentPosition.Y > ViewPortScaled.Y - SecurityBorderMax.Y)
		{
			CurrentPosition.Y = ViewPortScaled.Y - SecurityBorderMax.Y;
		}

		WindowSlot->SetPosition(CurrentPosition);
	}
}

void UBaseSimplyWindow::StartResizing()
{
	const UCanvasPanelSlot* WindowSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(Window);
	const FVector2D MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	ResizingOffset = WindowSlot->GetSize() - GetBodyRelativeOffset(MousePosition);
	bIsResizing = true;
	GetWindowManager()->SetHighestPriority(this);
}

void UBaseSimplyWindow::StopResizing()
{
	bIsResizing = false;
}

void UBaseSimplyWindow::CloseWindow()
{
	RemoveFromParent();
}

void UBaseSimplyWindow::HideWindow()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UBaseSimplyWindow::UnHideWindow()
{
	SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UBaseSimplyWindow::SetLocked(bool Locked)
{
	bLocked = Locked;
}

void UBaseSimplyWindow::SwitchLockedState()
{
	bLocked = !bLocked;
}

bool UBaseSimplyWindow::IsLocked() const
{
	return bLocked;
}

FVector2D UBaseSimplyWindow::GetBodyRelativeOffset(FVector2D PositionToMakeRelative) const
{
	const UCanvasPanelSlot* WindowSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(Window);
	return PositionToMakeRelative - WindowSlot->GetPosition();
}

void UBaseSimplyWindow::SetSimplyWindowPositionDirectly(FVector2D Position)
{
	UCanvasPanelSlot* WindowSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(Window);
	WindowSlot->SetPosition(Position);
}

void UBaseSimplyWindow::SetSimplyWindowPosition(ESimplyWindowPosition Position)
{
	FVector2D TargetLocation = FVector2D(0, 0);

	switch (Position)
	{
	case None: break;
	case TopLeft: break;
	case TopCenter:
		TargetLocation = USimplyWindowLibrary::GetRelativeViewportTopCenter(GetWorld(), this);
		break;
	case TopRight:
		TargetLocation = USimplyWindowLibrary::GetRelativeViewportTopRight(GetWorld(), this);
		break;
	case MiddleLeft:
		TargetLocation = USimplyWindowLibrary::GetRelativeViewportMiddleLeft(GetWorld(), this);
		break;
	case MiddleCenter:
		TargetLocation = USimplyWindowLibrary::GetRelativeViewportMiddleCenter(GetWorld(), this);
		break;
	case MiddleRight:
		TargetLocation = USimplyWindowLibrary::GetRelativeViewportMiddleRight(GetWorld(), this);
		break;
	case BottomLeft:
		TargetLocation = USimplyWindowLibrary::GetRelativeViewportBottomLeft(GetWorld(), this);
		break;
	case BottomCenter:
		TargetLocation = USimplyWindowLibrary::GetRelativeViewportBottomCenter(GetWorld(), this);
		break;
	case BottomRight:
		TargetLocation = USimplyWindowLibrary::GetRelativeViewportBottomRight(GetWorld(), this);
		break;
	}
	UCanvasPanelSlot* WindowSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(Window);
	WindowSlot->SetPosition(TargetLocation);
}

void UBaseSimplyWindow::NativeTick(const FGeometry& MovieSceneBlends, float InDeltaTime)
{
	Super::NativeTick(MovieSceneBlends, InDeltaTime);

	if (bLocked)
	{
		return;
	}
	if (bIsDragging)
	{
		UCanvasPanelSlot* WindowSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(Window);
		const FVector2D MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
		WindowSlot->SetPosition(MousePosition - DragOffset);
	}

	if (bIsResizing)
	{
		UCanvasPanelSlot* WindowSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(Window);
		const FVector2D MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
		FVector2D NewSize = GetBodyRelativeOffset(MousePosition + ResizingOffset);
		WindowSlot->SetSize(NewSize);

		if (bActiveMinWindowSize)
		{
			if (NewSize.X < MinWindowSize.X)
			{
				WindowSlot->SetSize(FVector2D(MinWindowSize.X, NewSize.Y));
				NewSize = WindowSlot->GetSize();
			}
			if (NewSize.Y < MinWindowSize.Y)
			{
				WindowSlot->SetSize(FVector2D(NewSize.X, MinWindowSize.Y));
				NewSize = WindowSlot->GetSize();
			}
		}
		if (bActiveMaxWindowSize)
		{
			if (NewSize.X > MaxWindowSize.X)
			{
				WindowSlot->SetSize(FVector2D(MaxWindowSize.X, NewSize.Y));
				NewSize = WindowSlot->GetSize();
			}
			if (NewSize.Y > MaxWindowSize.Y)
			{
				WindowSlot->SetSize(FVector2D(NewSize.X, MaxWindowSize.Y));
			}
		}
	}
}

USimplyWindowManager* UBaseSimplyWindow::GetWindowManager()
{
	TArray<UUserWidget*> FoundWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, USimplyWindowManager::StaticClass());

	if (FoundWidgets.Num() == 0)
	{
		USimplyWindowManager* WindowManager = CreateWidget<USimplyWindowManager>(this, Manager);
		WindowManager->AddToViewport(WindowManager->SimplyWindowsZOrder);
		return WindowManager;
	}
	return Cast<USimplyWindowManager>(FoundWidgets[0]);
}
