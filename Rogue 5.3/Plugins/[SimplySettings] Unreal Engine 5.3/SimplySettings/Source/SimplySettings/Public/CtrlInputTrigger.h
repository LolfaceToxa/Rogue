// Copyright Phoinix-DEV

#pragma once

#include "CoreMinimal.h"
#include "InputTriggers.h"
#include "CtrlInputTrigger.generated.h"

UCLASS(PerObjectConfig)
class UCtrlInputTrigger final : public UInputTrigger
{
	GENERATED_BODY()

public:
	virtual ETriggerState UpdateState_Implementation(const UEnhancedPlayerInput *PlayerInput, FInputActionValue ModifiedValue, float DeltaTime) override;
};