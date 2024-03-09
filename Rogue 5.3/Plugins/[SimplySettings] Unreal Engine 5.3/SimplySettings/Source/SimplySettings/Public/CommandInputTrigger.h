// Copyright Phoinix-DEV

#pragma once

#include "CoreMinimal.h"
#include "InputTriggers.h"
#include "CommandInputTrigger.generated.h"


UCLASS(meta = (DisplayName = "Simply Command Input Trigger"))
class SIMPLYSETTINGS_API UCommandInputTrigger : public UInputTrigger
{
	GENERATED_BODY()

public:
	virtual ETriggerState UpdateState_Implementation(const UEnhancedPlayerInput *PlayerInput, FInputActionValue ModifiedValue, float DeltaTime) override;
};
