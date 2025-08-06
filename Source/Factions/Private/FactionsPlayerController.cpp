// Fill out your copyright notice in the Description page of Project Settings.


#include "FactionsPlayerController.h"

void FactionsPlayerController::BeginPlay() {
    Super::BeginPlay();

    // Example logic: Show mouse cursor
    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableMouseOverEvents = true;
}