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
		
		UPROPERTY()
		AFactionsBoard* FactionsBoard;

};
