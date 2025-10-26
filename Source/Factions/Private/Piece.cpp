// Fill out your copyright notice in the Description page of Project Settings.

#include "Piece.h"
#include "FactionsBoard.h"
#include "FactionsCharacter.h"
#include "FactionsGameMode.h"
#include "Components/CapsuleComponent.h"
#include "kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "BoardSquare.h"
#include "FactionsPlayerController.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"

// Sets default values
APiece::APiece()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UCapsuleComponent *CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RootComponent"));
	RootComponent = CapsuleComponent;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	if (BaseMesh)
	{
		BaseMesh->SetupAttachment(RootComponent);
	}
	Orientation = FIntVector(1,1,0);
}

// Called when the game starts or when spawned
void APiece::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle MyTimerHandle;
	GetWorldTimerManager().SetTimer(MyTimerHandle, this, &APiece::SetInitialSquare, 0.2f, false);
	OrientedMovement = OrientMovement(Movement);
}

// Called every frame
void APiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Moving)
	{
		FVector CurrentLocation = GetActorLocation();
		FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, 3.0f);
		SetActorLocation(NewLocation);

		if (FVector::Dist(CurrentLocation, TargetLocation) <= 2.0f)
		{
			SetActorLocation(TargetLocation);
			Moving = false;
		}
	}
}

void APiece::PieceSelected()
{
	AFactionsPlayerController* PlayerController = Cast<AFactionsPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	AFactionsCharacter* FactionsCharacter = Cast<AFactionsCharacter>(PlayerController->GetPawn());
	if(FactionsCharacter == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("FactionsCharacter not valid"));
		return;
	}
	UE_LOG(LogTemp, Display, TEXT("%s is Player color vs %s is Color"), *FactionsCharacter->GetColor().ToString(), *Color.ToString());
	if(FactionsCharacter && FactionsCharacter->GetColor() != Color) // You can only select your own color pieces.
		return;
	FString Name = GetName();
	UE_LOG(LogTemp, Display, TEXT("%s selected"), *Name);
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFactionsBoard::StaticClass(), FoundActors);
	AFactionsBoard* FactionsBoard = Cast<AFactionsBoard>(FoundActors[0]);
	if (!IsValid(FactionsBoard))
	{
		UE_LOG(LogTemp, Display, TEXT("FactionsBoard not valid"));
	}
	if(FactionsCharacter->IsMyTurn())
	{
		FactionsBoard->SetSelectedPiece(this);
		FactionsBoard->UnHighlightAllSquares();
		FactionsBoard->HighlightSquares(OrientedMovement, BoardPosition);
		FVector CurrentLocation = GetActorLocation();
		SetActorLocation(CurrentLocation + RaiseHeight);
	}
}

void APiece::MoveToSquare(ABoardSquare *square)
{
	if (CurrentSquare != nullptr)
	{
		CurrentSquare->SetOccupyingPiece(nullptr); 
	}
	TargetLocation = square->GetActorLocation();
	if (square->GetOccupyingPiece() != nullptr)
		square->GetOccupyingPiece()->Destroy();
	Moving = true;
	AFactionsGameMode *FactionsGameMode = Cast<AFactionsGameMode>(UGameplayStatics::GetGameMode(this));
	BoardPosition[0] = square->GetCoordinates().Get<0>();
	BoardPosition[1] = square->GetCoordinates().Get<1>();
	square->SetOccupyingPiece(this);
	CurrentSquare = square;
	UE_LOG(LogTemp, Display, TEXT("Coordinates: %d, %d"), BoardPosition[0], BoardPosition[1]);
}

void APiece::PerformSpecial(ABoardSquare *Square)
{
	if (ParticleSystem)
	{
		if(SpawnedParticleSystem != nullptr) 
		{
			SpawnedParticleSystem->Deactivate();
			SpawnedParticleSystem = nullptr;
		}
		if(BlessedSquare != nullptr)
		{
			BlessedSquare->SetBlockAllButColor(FColor::Transparent);
			BlessedSquare = Square;
		}
		Square->SetBlockAllButColor(FColor::White);
        SpawnedParticleSystem = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
            GetWorld(),
            ParticleSystem,
            Square->GetActorLocation(),
            GetActorRotation(),
            FVector(1.0f), // Scale
            true, // Auto Activate
            true, // Reset if already active
            ENCPoolMethod::None, // Spawn section
			false
        );
	}
}

FColor APiece::GetColor()
{
	return Color;
}

void APiece::SetInitialSquare() 
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFactionsBoard::StaticClass(), FoundActors);
	for (AActor* Actor : FoundActors)
	{
		AFactionsBoard* FB = Cast<AFactionsBoard>(Actor);
		FString Message = FString::Printf(TEXT("Board Positions: %d, %d"), BoardPosition[0], BoardPosition[1]);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, Message);
		if (BoardPosition.Num() == 2) {
			CurrentSquare = FB->GetSquares()[(BoardPosition[0] * 8) + BoardPosition[1]];
			CurrentSquare->SetOccupyingPiece(this);
		}
		else 
		{
			UE_LOG(LogTemp, Warning, TEXT("Board Position not set!"));
		}
	}
}

FPieceMovement APiece::OrientMovement(FPieceMovement baseMovement)
{
	FPieceMovement NewMovement = FPieceMovement();
	for (int i = 0; i < baseMovement.RayMoveAttack.Num(); i++)
	{
		NewMovement.RayMoveAttack.Add(FIntVector(baseMovement.RayMoveAttack[i].X * Orientation.X, baseMovement.RayMoveAttack[i].Y * Orientation.Y, baseMovement.RayMoveAttack[i].Z));
	}
	for (int i = 0; i < baseMovement.JumpMoveAttack.Num(); i++)
	{
		NewMovement.JumpMoveAttack.Add(FIntVector(baseMovement.JumpMoveAttack[i].X * Orientation.X, baseMovement.JumpMoveAttack[i].Y * Orientation.Y, baseMovement.JumpMoveAttack[i].Z));
	}
	for (int i = 0; i < baseMovement.RayMove.Num(); i++)
	{
		NewMovement.RayMove.Add(FIntVector(baseMovement.RayMove[i].X * Orientation.X, baseMovement.RayMove[i].Y * Orientation.Y, baseMovement.RayMove[i].Z));
	}
	for (int i = 0; i < baseMovement.JumpMove.Num(); i++)
	{
		NewMovement.JumpMove.Add(FIntVector(baseMovement.JumpMove[i].X * Orientation.X, baseMovement.JumpMove[i].Y * Orientation.Y, baseMovement.JumpMove[i].Z));
	}
	for (int i = 0; i < baseMovement.RayAttack.Num(); i++)
	{
		NewMovement.RayAttack.Add(FIntVector(baseMovement.RayAttack[i].X * Orientation.X, baseMovement.RayAttack[i].Y * Orientation.Y, baseMovement.RayAttack[i].Z));
	}
	for (int i = 0; i < baseMovement.JumpAttack.Num(); i++)
	{
		NewMovement.JumpAttack.Add(FIntVector(baseMovement.JumpAttack[i].X * Orientation.X, baseMovement.JumpAttack[i].Y * Orientation.Y, baseMovement.JumpAttack[i].Z));
	}
	for (int i = 0; i < baseMovement.Bless.Num(); i++)
	{
		NewMovement.Bless.Add(FIntVector(baseMovement.Bless[i].X * Orientation.X, baseMovement.Bless[i].Y * Orientation.Y, baseMovement.Bless[i].Z));
	}
	for (int i = 0; i < baseMovement.Reanimate.Num(); i++)
	{
		NewMovement.Reanimate.Add(FIntVector(baseMovement.Reanimate[i].X * Orientation.X, baseMovement.Reanimate[i].Y * Orientation.Y, baseMovement.Reanimate[i].Z));
	}
	return NewMovement;
}
