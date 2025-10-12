// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Piece.generated.h"

UCLASS()
class FACTIONS_API APiece : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APiece();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	UFUNCTION()
	void BeginMouseOver(UPrimitiveComponent *TouchedComponent);

	UFUNCTION()
	void EndMouseOver(UPrimitiveComponent *TouchedComponent);

	UFUNCTION()
	void PieceSelected(UPrimitiveComponent *TouchedComponent, FKey InKey);

	UPROPERTY(EditAnywhere)
	bool isSelected = false;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent *BaseMesh;

	UPROPERTY(EditAnywhere, Category = "Piece Settings")
	FVector RaiseHeight;

	UPROPERTY(EditAnywhere, Category = "Piece Settings")
	TArray<int> MovesX;

	UPROPERTY(EditAnywhere, Category = "Piece Settings")
	TArray<int> MovesY;

	UPROPERTY(EditAnywhere, Category = "Piece Settings")
	TArray<int> BoardPosition;

	static APiece *SelectedPiece;

	UFUNCTION()
	void MoveToSquare(ABoardSquare *square);

	UFUNCTION()
	FString GetColor();

private:
	UPROPERTY(VisibleAnywhere)
	FVector TargetLocation;
	UPROPERTY(VisibleAnywhere)
	bool Moving = false;
	UPROPERTY(EditAnywhere)
	FString Color;
	ABoardSquare* CurrentSquare;
};
