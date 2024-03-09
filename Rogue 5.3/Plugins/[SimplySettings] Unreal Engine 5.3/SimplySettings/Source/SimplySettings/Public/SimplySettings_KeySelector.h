// Copyright Phoinix-DEV

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Components/InputKeySelector.h"
#include "InputMappingContext.h"
#include "EnhancedActionKeyMapping.h"
#include "SimplySettings_KeySelector.generated.h"

/**
 * Represents a single mapping for the UI
 */
UCLASS()
class SIMPLYSETTINGS_API USimplySettings_KeySelector : public UInputKeySelector
{
	GENERATED_BODY()

public:
	// A Key Selector is clearly identified by the Context, Action and Name combination
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	UInputMappingContext *Context;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	UInputAction *InputAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	FName MappingName;

	virtual void OnWidgetRebuilt() override;

	// A helper Method to fast define the selector
	UFUNCTION(BlueprintCallable, Category = "Simply Settings")
	virtual void InitializeSelector(UInputAction *InInputAction, UInputMappingContext *InContext, FName InMappingName);

	// Used to link the Mapping component to the settings, the Inputmappingname & Keyset has to be set before
	UFUNCTION(BlueprintCallable, Category = "Simply Settings")
	virtual void InitializeMapping();

	UFUNCTION(BlueprintCallable, Category = "Simply Settings")
	bool SelectKey(FInputChord Key);

	// Checks whether the given key is already bound in this keyset
	UFUNCTION(BlueprintCallable, Category = "Simply Settings")
	bool IsKeyAlreadyBound(FInputChord Key);

	// Helper function to get all the mappings bound to the given key
	TArray<FEnhancedActionKeyMapping *> GetMatchingMappingsFromContext(const FInputChord NewSelectedKey, UInputMappingContext *InContext);

	// The event is called, when a blacklisted key is selected
	UFUNCTION(BlueprintImplementableEvent, Category = "Simply Settings")
	void OnBlacklistedKeySelected(const UObject* World, const FInputChord PreviousKey, const FInputChord NewSelectedKey);

	UFUNCTION(BlueprintImplementableEvent, Category = "Simply Settings")
	void OnNewKeySelected(FInputChord NewKey);

protected:

	/** Differentiate between automatic binding and manual one
	 * This is required as there should be no userfeedback in the auto mode
	 */
	UPROPERTY(BlueprintReadWrite, Category = "Simply Settings")
	bool ManualMode = true;

private:
	UFUNCTION()
	void HandleNewKeySelected(FInputChord NewKey);

};
