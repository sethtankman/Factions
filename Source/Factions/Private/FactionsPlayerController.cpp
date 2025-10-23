// Fill out your copyright notice in the Description page of Project Settings.


#include "FactionsPlayerController.h"

AFactionsPlayerController::AFactionsPlayerController()
{
    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableMouseOverEvents = true;
}

FColor AFactionsPlayerController::GetPlayerColor()
{
    return PlayerColor;
}