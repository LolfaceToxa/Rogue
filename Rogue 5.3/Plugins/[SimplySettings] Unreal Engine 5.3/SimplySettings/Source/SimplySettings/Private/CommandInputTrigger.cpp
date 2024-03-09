// Copyright Phoinix-DEV

#include "CommandInputTrigger.h"
#include "EnhancedPlayerInput.h"

ETriggerState UCommandInputTrigger::UpdateState_Implementation(const UEnhancedPlayerInput *PlayerInput, FInputActionValue ModifiedValue, float DeltaTime)
{
    if (PlayerInput->IsPressed(FKey(EKeys::LeftCommand)) || PlayerInput->IsPressed(FKey(EKeys::RightCommand)))
    {
        return ETriggerState::Triggered;
    }
    return ETriggerState::None;
}
