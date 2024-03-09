// Copyright Phoinix-DEV

#include "CtrlInputTrigger.h"
#include "EnhancedPlayerInput.h"

ETriggerState UCtrlInputTrigger::UpdateState_Implementation(const UEnhancedPlayerInput *PlayerInput, FInputActionValue ModifiedValue, float DeltaTime)
{
    if (PlayerInput->IsPressed(FKey(EKeys::LeftControl)) || PlayerInput->IsPressed(FKey(EKeys::RightControl)))
    {
        return ETriggerState::Triggered;
    }
    return ETriggerState::None;
}
