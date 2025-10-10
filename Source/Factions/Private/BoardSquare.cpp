// Fill out your copyright notice in the Description page of Project Settings.

#include "BoardSquare.h"
#include "FactionsBoard.h"
#include "Piece.h"
#include "Components/BoxComponent.h"
#include "Templates/Tuple.h"
#include "FactionsGameMode.h"
#include "kismet/GameplayStatics.h"

// Sets default values
ABoardSquare::ABoardSquare()
{
	rank = 0;
	file = 0;
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Our root component will be a sphere that reacts to physics
	UBoxComponent *BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	RootComponent = BoxComponent;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	if (Mesh)
	{
		Mesh->SetupAttachment(RootComponent);
		Mesh->OnBeginCursorOver.AddDynamic(this, &ABoardSquare::BeginMouseOver);
		Mesh->OnEndCursorOver.AddDynamic(this, &ABoardSquare::EndMouseOver);
		Mesh->OnClicked.AddDynamic(this, &ABoardSquare::SelectSquare);
		PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLightComponent"));
		PointLight->SetupAttachment(Mesh);
		PointLight->SetHiddenInGame(true);
	}
}

void ABoardSquare::Init(int32 InRank, int32 InFile)
{
	rank = InRank;
	file = InFile;
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
	if (IsHidden() == false)
	{
		PointLight->SetHiddenInGame(false);
	}
}

void ABoardSquare::EndMouseOver(UPrimitiveComponent *TouchedComponent)
{
	PointLight->SetHiddenInGame(true);
}

void ABoardSquare::SelectSquare(UPrimitiveComponent *TouchedComponent, FKey key)
{
	if (IsHidden() == false)
	{
		Hide(true);
		AFactionsGameMode *FactionsGameMode = Cast<AFactionsGameMode>(UGameplayStatics::GetGameMode(this));
		APiece *SelectedPiece = FactionsGameMode->GetSelectedPiece();
		FactionsGameMode->FactionsBoard->UnHighlightAllSquares();
		SelectedPiece->MoveToSquare(this);
	}
}

void ABoardSquare::Hide(bool tf)
{
	SetActorHiddenInGame(tf);
}

TTuple<int, int> ABoardSquare::GetCoordinates()
{
	return MakeTuple(rank, file);
}