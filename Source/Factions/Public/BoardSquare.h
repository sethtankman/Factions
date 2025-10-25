// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Piece.h"
#include "Templates/Tuple.h"
#include "GameFramework/Actor.h"
#include "Components/PointLightComponent.h"
#include "BoardSquare.generated.h"

UCLASS()
class FACTIONS_API ABoardSquare : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABoardSquare();

	void Init(int32 x, int32 y);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent *MoveCaptureMesh;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent *SpecialMesh;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent *RemoteCaptureMesh;

	UPROPERTY(EditAnywhere)
	UPointLightComponent *PointLight;

	UFUNCTION()
	void BeginMouseOver(UPrimitiveComponent *TouchedComponent);

	UFUNCTION()
	void EndMouseOver(UPrimitiveComponent *TouchedComponent);

	UFUNCTION()
	void SelectSquare(UPrimitiveComponent *TouchedComponent, FKey key);

	UFUNCTION()
	void Hide(bool tf, FColor color);

	UFUNCTION()
	void SetOccupyingPiece(APiece* piece);

	UFUNCTION()
	void SetBlockAllButColor(FColor BlockColor);
	
	UFUNCTION()
	APiece* GetOccupyingPiece();

	TTuple<int, int> GetCoordinates();

	UFUNCTION()
	FColor GetBlockAllButColor();

private:
	int rank;
	int file;
	bool hidden;
	APiece* OccupyingPiece;
	FColor BlockAllButColor = FColor::Transparent;

	void SelectHighlightedSquare();
};
