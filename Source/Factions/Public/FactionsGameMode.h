// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FactionsGameMode.generated.h"

class AFactionsBoard;

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
	void SetSelectedPiece(APiece *piece);

	UFUNCTION()
	APiece* GetSelectedPiece();

	UFUNCTION()
	FString GetCurrentPlayer();

	UFUNCTION()
	FString StartNextTurn();

	UFUNCTION()
	FString AssignMyColor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	APiece *SelectedPiece;
	UPROPERTY() 
	FString CurrentPlayer;
	UPROPERTY()
	TArray<FString> AllColors;

	int ColorAssignIndex = 0;
};
