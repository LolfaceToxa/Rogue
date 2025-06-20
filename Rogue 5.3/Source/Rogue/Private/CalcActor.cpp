// Fill out your copyright notice in the Description page of Project Settings.


#include "CalcActor.h"

// Sets default values
ACalcActor::ACalcActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACalcActor::BeginPlay()
{
	Super::BeginPlay();
	
}


TArray<FVector2D> ACalcActor::SpiralTraversalFromCenter(int32 Rows, int32 Cols, FVector2D Center, int32 Radius)
{
    TArray<TArray<FVector2D>> Matrix;
    Matrix.SetNum(Rows);
    for (int32 i = 0; i < Rows; ++i)
    {
        Matrix[i].SetNum(Cols);
        for (int32 j = 0; j < Cols; ++j)
        {
            Matrix[i][j] = FVector2D(i, j);
        }
    }

    int32 CenterX = Center.X;
    int32 CenterY = Center.Y;

    TArray<FVector2D> Directions = { FVector2D(0, 1), FVector2D(1, 0), FVector2D(0, -1), FVector2D(-1, 0) };
    TSet<FVector2D> Visited;
    TArray<FVector2D> Result;
    int32 X = CenterX, Y = CenterY;
    int32 DirIndex = 0;
    int32 Steps = 1;

    Result.Add(Matrix[X][Y]);
    Visited.Add(FVector2D(X, Y));

    while (true)
    {
        bool bReachedRadius = false;
        for (int32 i = 0; i < 2; ++i)
        {
            for (int32 j = 0; j < Steps; ++j)
            {
                X += Directions[DirIndex].X;
                Y += Directions[DirIndex].Y;

                if (X >= 0 && X < Rows && Y >= 0 && Y < Cols && !Visited.Contains(FVector2D(X, Y)))
                {
                    if (FMath::Abs(X - CenterX) > Radius || FMath::Abs(Y - CenterY) > Radius)
                    {
                        bReachedRadius = true;
                        break;
                    }
                    Result.Add(Matrix[X][Y]);
                    Visited.Add(FVector2D(X, Y));
                }
            }
            if (bReachedRadius)
            {
                break;
            }
            DirIndex = (DirIndex + 1) % 4;
        }
        if (bReachedRadius)
        {
            break;
        }
        ++Steps;
    }

    return Result;
}

TSet<FVector2D> ACalcActor::ExcludeDiff(int32 Rows, int32 Cols, TArray<FVector2D> Inner)
{
    TArray<TArray<FVector2D>> Matrix;
    Matrix.SetNum(Rows);
    for (int32 i = 0; i < Rows; ++i)
    {
        Matrix[i].SetNum(Cols);
        for (int32 j = 0; j < Cols; ++j)
        {
            Matrix[i][j] = FVector2D(i, j);
        }
    }

    TSet<FVector2D> Outer;

    for (int32 i = 0; i < Cols; ++i)
    {
        for (int32 j = 0; j < Rows; ++j) {
            for (int k = 0; k < Inner.Num(); k++) {
                if (Matrix[i][j] == Inner[i]) {
                    continue;
                }
                Outer.Add(Matrix[i][j]);
            }
        }
    }
    return Outer;
}

