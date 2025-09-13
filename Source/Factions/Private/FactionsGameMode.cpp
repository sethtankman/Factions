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