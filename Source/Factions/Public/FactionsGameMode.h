// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FactionsGameMode.generated.h"

class AFactionsBoard;
class AFactionsCharacter;
class APiece;

/**
 *
 */
UCLASS()
class FACTIONS_API AFactionsGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	// Sets default values for Faction Game Mode
	AFactionsGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Elements")
	AFactionsBoard *FactionsBoard;

	UFUNCTION()
	FColor GetCurrentPlayerColor();

	UFUNCTION()
	FColor StartNextTurn();

	UFUNCTION()
	FColor AssignMyColor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY() 
	FColor CurrentPlayerColor;
	UPROPERTY()
	TArray<FColor> AllColors;
	UPROPERTY()
	TArray<AFactionsCharacter*> Players;

	int ColorAssignIndex = 0;
};
