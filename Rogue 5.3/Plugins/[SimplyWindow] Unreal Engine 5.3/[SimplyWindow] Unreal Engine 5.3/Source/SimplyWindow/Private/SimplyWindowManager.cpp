// Fill out your copyright notice in the Description page of Project Settings.


#include "SimplyWindowManager.h"
#include "BaseSimplyWindow.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

void USimplyWindowManager::SetHighestPriority(UBaseSimplyWindow* Window) const
{
	TArray<UWidget*> Children = MainPanel->GetAllChildren();
	TArray<UBaseSimplyWindow*> SimplyWindows;

	for (UWidget* Widget : Children)
	{
		UBaseSimplyWindow* SimplyWindow = Cast<UBaseSimplyWindow>(Widget);
		if (SimplyWindow)
		{
			SimplyWindows.Add(SimplyWindow);
		}
	}

	SimplyWindows.Sort([](const UBaseSimplyWindow& A, const UBaseSimplyWindow& B)
	{
		const UCanvasPanelSlot* ASlot = Cast<UCanvasPanelSlot>(A.Slot);
		const UCanvasPanelSlot* BSlot = Cast<UCanvasPanelSlot>(B.Slot);
		return ASlot->GetZOrder() > BSlot->GetZOrder();
	});

	SimplyWindows.Remove(Window);

	for (int i = 0; i < SimplyWindows.Num(); i++)
	{
		UCanvasPanelSlot* ASlot = Cast<UCanvasPanelSlot>(SimplyWindows[i]->Slot);
		ASlot->SetZOrder(i);
	}

	UCanvasPanelSlot* ASlot = Cast<UCanvasPanelSlot>(Window->Slot);
	ASlot->SetZOrder(SimplyWindows.Num() + 1);
}
