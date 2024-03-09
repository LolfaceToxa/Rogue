// Copyright Phoinix-DEV

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GraphicsSettingsWidget.generated.h"

UCLASS()
class SIMPLYSETTINGS_API UGraphicsSettingsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable, Category="Simply Settings")
	virtual void SaveGraphicSettings();

	UFUNCTION(BlueprintCallable, Category="Simply Settings")
	virtual void DiscardGraphicSettings();

	UFUNCTION(BlueprintImplementableEvent, Category="Simply Settings")
	void VideoSecurityCheck();

	// Helper
	UFUNCTION(BlueprintCallable, Category="Simply Settings")
	static FIntPoint ResStringToIntPoint(FString ResString);

private:
	// This is cached as not stored in config, required for discard
	float CachedResScale;
};
