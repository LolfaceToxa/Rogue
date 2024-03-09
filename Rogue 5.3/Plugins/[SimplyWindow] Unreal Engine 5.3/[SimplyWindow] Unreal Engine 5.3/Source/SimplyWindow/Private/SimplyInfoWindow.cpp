// Fill out your copyright notice in the Description page of Project Settings.


#include "SimplyInfoWindow.h"

void USimplyInfoWindow::Confirm()
{
	if (ConfirmDelegate.IsBound())
	{
		ConfirmDelegate.Broadcast();
	}
	RemoveFromParent();
}
