// Fill out your copyright notice in the Description page of Project Settings.


#include "CreateSimplyConfirmationWindow.h"
#include "SimplyConfirmationWindow.h"
#include "SimplyWindowManager.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"

UCreateSimplyConfirmationWindow* UCreateSimplyConfirmationWindow::CreateSimplyConfirmationWindow(
	const UObject* WorldContextObject, TSubclassOf<USimplyConfirmationWindow> ConfirmationWindow, FText Text,
	FVector2D Position, bool Draggable)
{
	UCreateSimplyConfirmationWindow* BlueprintNode = NewObject<UCreateSimplyConfirmationWindow>();
	BlueprintNode->WorldContextObject = WorldContextObject;
	BlueprintNode->WindowClass = ConfirmationWindow;
	BlueprintNode->ConfirmationText = Text;
	BlueprintNode->TargetPosition = Position;
	BlueprintNode->bDraggable = Draggable;
	return BlueprintNode;
}

void UCreateSimplyConfirmationWindow::Activate()
{
	Super::Activate();

	SimplyWindow = CreateWidget<USimplyConfirmationWindow>(
		WorldContextObject->GetWorld()->GetFirstPlayerController(),
		WindowClass);

	if (SimplyWindow)
	{
		if (TargetPosition.Size() > 0)
		{
			SimplyWindow->SetSimplyWindowPositionDirectly(TargetPosition);
		}
		else
		{
			SimplyWindow->SetSimplyWindowPosition(ESimplyWindowPosition::MiddleCenter);
		}

		SimplyWindow->GetWindowManager()->MainPanel->AddChild(SimplyWindow);
		SimplyWindow->ConfirmationText->SetText(ConfirmationText);
		SimplyWindow->ConfirmDelegate.AddDynamic(this, &UCreateSimplyConfirmationWindow::Confirm);
		SimplyWindow->AbortDelegate.AddDynamic(this, &UCreateSimplyConfirmationWindow::Abort);
		OnWindowCreated.Broadcast(SimplyWindow);
	}
}

void UCreateSimplyConfirmationWindow::Confirm()
{
	OnConfirm.Broadcast();
}

void UCreateSimplyConfirmationWindow::Abort()
{
	OnAbort.Broadcast();
}
