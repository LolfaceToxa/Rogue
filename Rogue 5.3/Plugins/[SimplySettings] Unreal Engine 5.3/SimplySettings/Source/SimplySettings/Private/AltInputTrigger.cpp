// Copyright Phoinix-DEV

#include "AltInputTrigger.h"
#include "EnhancedPlayerInput.h"

ETriggerState UAltInputTrigger::UpdateState_Implementation(const UEnhancedPlayerInput *PlayerInput, FInputActionValue ModifiedValue, float DeltaTime)
{
    if (PlayerInput->IsPressed(FKey(EKeys::LeftAlt)) || PlayerInput->IsPressed(FKey(EKeys::RightAlt)))
    {
        return ETriggerState::Triggered;
    }
    return ETriggerState::None;
}
