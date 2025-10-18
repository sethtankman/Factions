// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPieceMovement.h"
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
	
	UFUNCTION()
	void PieceSelected();

	UPROPERTY(EditAnywhere)
	bool isSelected = false;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent *BaseMesh;

	UPROPERTY(EditAnywhere, Category = "Piece Settings")
	FVector RaiseHeight;

	UPROPERTY(EditAnywhere, Category = "Piece Settings")
	FPieceMovement Movement;

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
	UFUNCTION()
	void SetInitialSquare();
	ABoardSquare* CurrentSquare;
};
