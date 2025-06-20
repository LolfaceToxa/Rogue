// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CalcActor.generated.h"

UCLASS(BlueprintType)
class ROGUE_API ACalcActor : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ACalcActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintCallable, Category = "SpiralMatrix")
	TArray<FVector2D> SpiralTraversalFromCenter(int32 Rows, int32 Cols, FVector2D Center, int32 Radius);
	UFUNCTION(BlueprintCallable, Category = "ExcludeDiff")
	TSet<FVector2D> ExcludeDiff(int32 Rows, int32 Cols, TArray<FVector2D> Inner);
};
