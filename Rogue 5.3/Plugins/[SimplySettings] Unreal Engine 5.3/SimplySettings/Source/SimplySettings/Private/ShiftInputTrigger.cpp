// Fill out your copyright notice in the Description page of Project Settings.

#include "ShiftInputTrigger.h"
#include "EnhancedPlayerInput.h"

ETriggerState UShiftInputTrigger::UpdateState_Implementation(const UEnhancedPlayerInput *PlayerInput, FInputActionValue ModifiedValue, float DeltaTime)
{
    if (PlayerInput->IsPressed(FKey(EKeys::LeftShift)) || PlayerInput->IsPressed(FKey(EKeys::RightShift)))
    {
        return ETriggerState::Triggered;
    }
    return ETriggerState::None;
}
