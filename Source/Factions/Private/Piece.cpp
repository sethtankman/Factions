// Fill out your copyright notice in the Description page of Project Settings.

#include "Piece.h"
#include "FactionsBoard.h"
#include "FactionsGameMode.h"
#include "Components/CapsuleComponent.h"
#include "kismet/GameplayStatics.h"
#include "BoardSquare.h"

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
		BaseMesh->OnBeginCursorOver.AddDynamic(this, &APiece::BeginMouseOver);
		BaseMesh->OnClicked.AddDynamic(this, &APiece::PieceSelected);
	}
}

// Called when the game starts or when spawned
void APiece::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle MyTimerHandle;
	GetWorldTimerManager().SetTimer(MyTimerHandle, this, &APiece::SetInitialSquare, 0.2f, false);
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

// Called to bind functionality to input
void APiece::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APiece::EndMouseOver(UPrimitiveComponent *TouchedComponent) {}

void APiece::BeginMouseOver(UPrimitiveComponent *TouchedComponent)
{
}

void APiece::PieceSelected(UPrimitiveComponent *TouchedComponent, FKey InKey)
{
	FString Name = GetName();
	UE_LOG(LogTemp, Display, TEXT("%s selected"), *Name);
	AFactionsGameMode *FactionsGameMode = Cast<AFactionsGameMode>(UGameplayStatics::GetGameMode(this));
	if (!IsValid(FactionsGameMode))
	{
		UE_LOG(LogTemp, Display, TEXT("FactionsGameMode not valid"), *Name);
	}
	if (!IsValid(FactionsGameMode->FactionsBoard))
	{
		UE_LOG(LogTemp, Display, TEXT("FactionsBoard not valid"), *Name);
	}
	FactionsGameMode->SetSelectedPiece(this);
	FactionsGameMode->FactionsBoard->UnHighlightAllSquares();
	FactionsGameMode->FactionsBoard->HighlightSquares(Movement, BoardPosition);
	FVector CurrentLocation = GetActorLocation();
	SetActorLocation(CurrentLocation + RaiseHeight);
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

FString APiece::GetColor()
{
	return Color;
}

void APiece::SetInitialSquare() 
{
	AFactionsGameMode *FactionsGameMode = Cast<AFactionsGameMode>(UGameplayStatics::GetGameMode(this));
	UE_LOG(LogTemp, Display, TEXT("Set Initial Square Called"));
	if (BoardPosition.Num() == 2) {
		CurrentSquare = FactionsGameMode->FactionsBoard->GetSquares()[(BoardPosition[0] * 8) + BoardPosition[1]];
		CurrentSquare->SetOccupyingPiece(this);
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("Board Position not set!"));
	}
}
