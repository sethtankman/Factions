// Fill out your copyright notice in the Description page of Project Settings.


#include "FactionsBoard.h"
#include "BoardSquare.h"
#include <cmath>

// Sets default values
AFactionsBoard::AFactionsBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFactionsBoard::BeginPlay()
{
	Super::BeginPlay();
	Squares.Reserve(64);
	FVector Offset = FVector(360, 360, 40);
	float SquareSize = -104;
	for(int i = 0; i< 64; i++) {
		FVector SquarePlacement = FVector((i / 8) * SquareSize, (i % 8) * SquareSize, 0);
		Squares.Emplace(GetWorld()->SpawnActor<ABoardSquare>(BP_BoardSquareClass, GetActorLocation() + Offset + SquarePlacement, GetActorRotation()));
	}
}

// Called every frame
void AFactionsBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFactionsBoard::HighlightSquares(TArray<int> x, TArray<int> y, TArray<int> PiecePosition) 
{

	for(int i = 0; i < x.Num(); i++)
	{
		int boardPositionX = PiecePosition[0] + x[i];
		int boardPositionY = PiecePosition[1] + y[i];
		if(IsValidSquare(boardPositionX, boardPositionY)) 
		{
			Squares[(boardPositionX*8)+boardPositionY]->Hide(false);
		}
	}
}

bool AFactionsBoard::IsValidSquare(int x, int y) {
	return x >= 0 && x < 8 && y >= 0 && y < 8;
}
