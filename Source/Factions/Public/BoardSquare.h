// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoardSquare.generated.h"

UCLASS()
class FACTIONS_API ABoardSquare : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoardSquare();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere) 
	UStaticMeshComponent* Mesh;

	UFUNCTION()
	void BeginMouseOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void EndMouseOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void Hide(bool tf);

};
