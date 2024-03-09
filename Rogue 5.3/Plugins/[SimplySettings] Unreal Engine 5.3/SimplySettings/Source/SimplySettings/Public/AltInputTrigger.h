// Copyright Phoinix-DEV

#pragma once

#include "CoreMinimal.h"
#include "InputTriggers.h"
#include "AltInputTrigger.generated.h"


UCLASS(meta = (DisplayName = "Simply Alt Input Trigger"))
class SIMPLYSETTINGS_API UAltInputTrigger : public UInputTrigger
{
	GENERATED_BODY()

public:
	virtual ETriggerState UpdateState_Implementation(const UEnhancedPlayerInput *PlayerInput, FInputActionValue ModifiedValue, float DeltaTime) override;
};
