// Fill out your copyright notice in the Description page of Project Settings.

#include "BoardSquare.h"
#include "Components/BoxComponent.h"

// Sets default values
ABoardSquare::ABoardSquare()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Our root component will be a sphere that reacts to physics
	UBoxComponent* BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
    RootComponent = BoxComponent;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	if(Mesh) {
		Mesh->SetupAttachment(RootComponent);
		Mesh->OnBeginCursorOver.AddDynamic(this, &ABoardSquare::BeginMouseOver);
		Mesh->OnEndCursorOver.AddDynamic(this, &ABoardSquare::EndMouseOver);
		PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLightComponent"));
		PointLight->SetupAttachment(Mesh);
		PointLight->SetHiddenInGame(true);
	}
}

// Called when the game starts or when spawned
void ABoardSquare::BeginPlay()
{
	Super::BeginPlay();
	Hide(true);
}

// Called every frame
void ABoardSquare::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABoardSquare::BeginMouseOver(UPrimitiveComponent *TouchedComponent)
{
	if(IsHidden() == false) {
		PointLight->SetHiddenInGame(false);
	}
}

void ABoardSquare::EndMouseOver(UPrimitiveComponent *TouchedComponent)
{
	PointLight->SetHiddenInGame(true);
}

void ABoardSquare::Hide(bool tf) 
{
	SetActorHiddenInGame(tf);
}
