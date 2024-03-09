// Copyright Phoinix-DEV

#pragma once

#include "CoreMinimal.h"
#include "InputTriggers.h"
#include "ShiftInputTrigger.generated.h"

UCLASS(meta = (DisplayName = "Simply Shift Input Trigger"))
class SIMPLYSETTINGS_API UShiftInputTrigger : public UInputTrigger
{
	GENERATED_BODY()

public:
	virtual ETriggerState UpdateState_Implementation(const UEnhancedPlayerInput *PlayerInput, FInputActionValue ModifiedValue, float DeltaTime) override;
};
