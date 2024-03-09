// Fill out your copyright notice in the Description page of Project Settings.


#include "SimplyConfirmationWindow.h"

void USimplyConfirmationWindow::HideWindow()
{
	Super::HideWindow();
	if (AbortDelegate.IsBound())
	{
		AbortDelegate.Broadcast();
	}
}

void USimplyConfirmationWindow::CloseWindow()
{
	Super::CloseWindow();
	if (AbortDelegate.IsBound())
	{
		AbortDelegate.Broadcast();
	}
}

void USimplyConfirmationWindow::Confirm()
{
	if (ConfirmDelegate.IsBound())
	{
		ConfirmDelegate.Broadcast();
	}
	RemoveFromParent();
}
