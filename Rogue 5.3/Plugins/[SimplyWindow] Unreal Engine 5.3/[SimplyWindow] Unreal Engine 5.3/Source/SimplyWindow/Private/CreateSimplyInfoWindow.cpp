// Fill out your copyright notice in the Description page of Project Settings.


#include "CreateSimplyInfoWindow.h"
#include "SimplyInfoWindow.h"
#include "SimplyWindowManager.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"

UCreateSimplyInfoWindow* UCreateSimplyInfoWindow::CreateSimplyInfoWindow(const UObject* WorldContextObject,
                                                                         TSubclassOf<USimplyInfoWindow>
                                                                         InfoWindow, FText Text,
                                                                         FVector2D Position, bool Draggable)
{
	UCreateSimplyInfoWindow* BlueprintNode = NewObject<UCreateSimplyInfoWindow>();
	BlueprintNode->WorldContextObject = WorldContextObject;
	BlueprintNode->WindowClass = InfoWindow;
	BlueprintNode->InfoText = Text;
	BlueprintNode->TargetPosition = Position;;
	BlueprintNode->bDraggable = Draggable;
	return BlueprintNode;
}

void UCreateSimplyInfoWindow::Activate()
{
	Super::Activate();

	SimplyWindow = CreateWidget<USimplyInfoWindow>(
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
		SimplyWindow->InfoText->SetText(InfoText);
		SimplyWindow->ConfirmDelegate.AddDynamic(this, &UCreateSimplyInfoWindow::Confirm);
		OnWindowCreated.Broadcast(SimplyWindow);
	}
}

void UCreateSimplyInfoWindow::Confirm()
{
	OnConfirm.Broadcast();
}
