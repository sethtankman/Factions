// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FactionsPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FACTIONS_API AFactionsPlayerController : public APlayerController
{
	GENERATED_BODY()
	public:
		// Sets default values for Faction Game Mode
		AFactionsPlayerController();

		UFUNCTION()
		FString GetPlayerColor();
	private:
		UPROPERTY(EditAnywhere)
		FString PlayerColor;
};
