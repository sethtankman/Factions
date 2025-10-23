// Fill out your copyright notice in the Description page of Project Settings.


#include "FactionsGameMode.h"
#include "FactionsBoard.h"
#include "FactionsPlayerController.h"
#include "FactionsCharacter.h"
#include "Kismet/GameplayStatics.h"

AFactionsGameMode::AFactionsGameMode()
{
    PlayerControllerClass = AFactionsPlayerController::StaticClass();
    ColorAssignIndex = 0;
    AllColors = {
        TEXT("white"),
        TEXT("black"),
        TEXT("red"),
        TEXT("blue")
    };
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

void AFactionsGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    if (NewPlayer)
    {
        APawn* ControlledPawn = NewPlayer->GetPawn();
        if (ControlledPawn)
        {
            AFactionsCharacter* MyCharacter = Cast<AFactionsCharacter>(ControlledPawn);
            if (MyCharacter)
            {
                MyCharacter->SetColor(AssignMyColor());
            }
        }
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

FString AFactionsGameMode::AssignMyColor()
{
    UE_LOG(LogTemp, Warning, TEXT("Color Assign index %d"), ColorAssignIndex);
    FString AssignedColor = AllColors[ColorAssignIndex];
    ColorAssignIndex++;
    return AssignedColor;
}

APiece* AFactionsGameMode::GetSelectedPiece()
{
    return SelectedPiece;
}

FString AFactionsGameMode::GetCurrentPlayer()
{
    return CurrentPlayer;
}