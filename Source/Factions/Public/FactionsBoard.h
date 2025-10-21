// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPieceMovement.h"
#include "FactionsBoard.generated.h"

class ABoardSquare;

UCLASS()
class FACTIONS_API AFactionsBoard : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFactionsBoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HighlightSquares(FPieceMovement Movement, TArray<int> PiecePosition);

	void UnHighlightAllSquares();

	UPROPERTY(EditAnywhere, Category = "Board Settings")
	TSubclassOf<ABoardSquare> BP_BoardSquareClass;

	TArray<ABoardSquare *> GetSquares();

private:
	UFUNCTION()
	bool IsValidSquare(int x, int y, bool CanSelectFriendlies);

	bool HighlightSquare(int BoardPositionX, int BoardPositaionY, FString color);
	
	UPROPERTY(EditAnywhere, Category = "Board Settings")
	TArray<ABoardSquare *> Squares;
};
