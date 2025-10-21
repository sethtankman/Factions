// Fill out your copyright notice in the Description page of Project Settings.

#include "FactionsBoard.h"
#include "FactionsGameMode.h"
#include "BoardSquare.h"
#include "kismet/GameplayStatics.h"
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
	for (int i = 0; i < 64; i++)
	{
		FVector SquarePlacement = FVector((i / 8) * SquareSize, (i % 8) * SquareSize, 0);
		ABoardSquare *Square = GetWorld()->SpawnActor<ABoardSquare>(BP_BoardSquareClass, GetActorLocation() + Offset + SquarePlacement, GetActorRotation());
		Square->Init(SquarePlacement[0] / SquareSize, SquarePlacement[1] / SquareSize);
		Squares.Emplace(Square);
	}
}

// Called every frame
void AFactionsBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFactionsBoard::HighlightSquares(FPieceMovement Movement, TArray<int> PiecePosition)
{
	if(Movement.RayMoveAttack.Num() != 0) {
		for (int ray = 0; ray < Movement.RayMoveAttack.Num(); ray++) 
		{
			for (int distance = 1; distance <= Movement.RayMoveAttack[ray].Z; distance++)
			{
				int BoardPositionX = PiecePosition[0] + (Movement.RayMoveAttack[ray].X * distance);
				int BoardPositionY = PiecePosition[1] + (Movement.RayMoveAttack[ray].Y * distance);
				if (HighlightSquare(BoardPositionX, BoardPositionY, "green") == false) 
				{
					break;
				}
			}
		}
	}
	if(Movement.JumpMoveAttack.Num() != 0) {
		for (int coordinate = 0; coordinate < Movement.JumpMoveAttack.Num(); coordinate++) 
		{
			HighlightSquare(PiecePosition[0] + Movement.JumpMoveAttack[coordinate].X, PiecePosition[1] + Movement.JumpMoveAttack[coordinate].Y, "green");
		}
	}
	if(Movement.RayMove.Num() != 0) {

	}
	if (Movement.JumpMove.Num() != 0) {
		int boardPositionX = PiecePosition[0] + 0;
		int boardPositionY = PiecePosition[1] + 0;
		if (IsValidSquare(boardPositionX, boardPositionY, false))
		{
			Squares[(boardPositionX * 8) + boardPositionY]->Hide(false, "green");
		}
	}
	if (Movement.RayAttack.Num() != 0) {
	}
	if (Movement.JumpAttack.Num() != 0) {
		for (int coordinate = 0; coordinate < Movement.JumpAttack.Num(); coordinate++) 
		{
			HighlightSquare(PiecePosition[0] + Movement.JumpAttack[coordinate].X, PiecePosition[1] + Movement.JumpAttack[coordinate].Y, "red");
		}
	}
	if (Movement.Bless.Num() != 0) 
	{	
		for (int coordinate = 0; coordinate < Movement.Bless.Num(); coordinate++) 
		{
			HighlightSquare(PiecePosition[0] + Movement.Bless[coordinate].X, PiecePosition[1] + Movement.Bless[coordinate].Y, "blue");
		}
	}
	if (Movement.Reanimate.Num() != 0) {

	}
}

bool AFactionsBoard::HighlightSquare(int BoardPositionX, int BoardPositionY, FString color) 
{
	UE_LOG(LogTemp, Display, TEXT("X: %d, Y: %d"), BoardPositionX, BoardPositionY);
	bool CanSelectFriendlies = (color == "blue");
	if (IsValidSquare(BoardPositionX, BoardPositionY, CanSelectFriendlies))
	{
		UE_LOG(LogTemp, Display, TEXT("Valid!"));
		Squares[(BoardPositionX * 8) + BoardPositionY]->Hide(false, color);
		return true;
	}
	return false;
}

void AFactionsBoard::UnHighlightAllSquares()
{
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			Squares[(x * 8) + y]->Hide(true, "None");
		}
	}
}

bool AFactionsBoard::IsValidSquare(int x, int y, bool CanSelectFriendlies)
{
	bool inBounds = x >= 0 && x < 8 && y >= 0 && y < 8;
	if (inBounds) 
	{
		ABoardSquare* Square = Squares[(x * 8) + y];
		AFactionsGameMode *FactionsGameMode = Cast<AFactionsGameMode>(UGameplayStatics::GetGameMode(this));
		if (Square->GetOccupyingPiece() == nullptr)
		{
			return true;
		} 
		else if(FactionsGameMode->GetSelectedPiece() != nullptr && CanSelectFriendlies == false)
		{
			return Square->GetOccupyingPiece()->GetColor() != FactionsGameMode->GetSelectedPiece()->GetColor();
		} else if (FactionsGameMode->GetSelectedPiece() != nullptr && CanSelectFriendlies == true) {
			return Square->GetOccupyingPiece()->GetColor() == FactionsGameMode->GetSelectedPiece()->GetColor();
		}
	}
	return false;
}

TArray<ABoardSquare *> AFactionsBoard::GetSquares()
{
	return Squares;
}
