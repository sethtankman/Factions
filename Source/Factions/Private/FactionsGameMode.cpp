// Fill out your copyright notice in the Description page of Project Settings.


#include "FactionsGameMode.h"
#include "FactionsBoard.h"
#include "FactionsPlayerController.h"
#include "Kismet/GameplayStatics.h"

AFactionsGameMode::AFactionsGameMode()
{
    PlayerControllerClass = AFactionsPlayerController::StaticClass();
}

// Called when the game starts or when spawned
void AFactionsGameMode::BeginPlay()
{
	Super::BeginPlay();
    CurrentPlayer = "white"; // TODO: stand-in for some sort of randomization
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFactionsBoard::StaticClass(), FoundActors);
    if(FoundActors.Num() > 0) {
        FactionsBoard = Cast<AFactionsBoard>(FoundActors[0]);
        if (FactionsBoard)
        {
            UE_LOG(LogTemp, Log, TEXT("Found FactionsBoard: %s"), *FactionsBoard->GetName());
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("First actor found wasn't an AFactionsBoard"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No FactionsBoard found in level!"));
    }
}

// TODO: Stand-in for more complex logic
FString AFactionsGameMode::StartNextTurn()
{
    if (CurrentPlayer == "black")
        CurrentPlayer = "white";
    else
        CurrentPlayer = "black";
    return CurrentPlayer;
}

void AFactionsGameMode::SetSelectedPiece(APiece *piece) 
{
    SelectedPiece = piece;
}

APiece* AFactionsGameMode::GetSelectedPiece()
{
    return SelectedPiece;
}

FString AFactionsGameMode::GetCurrentPlayer()
{
    return CurrentPlayer;
}