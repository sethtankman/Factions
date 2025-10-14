// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPieceMovement.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FPieceMovement
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<FIntVector> RayMoveAttack;
	UPROPERTY(EditAnywhere)
	TArray<FIntVector> JumpMoveAttack;
	UPROPERTY(EditAnywhere)
	TArray<FIntVector> RayMove;
	UPROPERTY(EditAnywhere)
	TArray<FIntVector> JumpMove;
	UPROPERTY(EditAnywhere)
	TArray<FIntVector> RayAttack;
	UPROPERTY(EditAnywhere)
	TArray<FIntVector> JumpAttack;
	UPROPERTY(EditAnywhere)
	TArray<FIntVector> Bless;
	UPROPERTY(EditAnywhere)
	TArray<FIntVector> Reanimate;
};
