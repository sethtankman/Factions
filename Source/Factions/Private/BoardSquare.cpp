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
	hidden = true;
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Our root component will be a sphere that reacts to physics
	UBoxComponent *BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	RootComponent = BoxComponent;
	Mesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh1"));
	if (Mesh1)
	{
		Mesh1->SetupAttachment(RootComponent);
		Mesh1->OnBeginCursorOver.AddDynamic(this, &ABoardSquare::BeginMouseOver);
		Mesh1->OnEndCursorOver.AddDynamic(this, &ABoardSquare::EndMouseOver);
		Mesh1->OnClicked.AddDynamic(this, &ABoardSquare::SelectSquare);
	}
	Mesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh2"));
	if (Mesh2)
	{
		Mesh2->SetupAttachment(RootComponent);
		Mesh2->OnBeginCursorOver.AddDynamic(this, &ABoardSquare::BeginMouseOver);
		Mesh2->OnEndCursorOver.AddDynamic(this, &ABoardSquare::EndMouseOver);
		Mesh2->OnClicked.AddDynamic(this, &ABoardSquare::SelectSquare);
	}
	Mesh3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh3"));
	if (Mesh3)
	{
		Mesh3->SetupAttachment(RootComponent);
		Mesh3->OnBeginCursorOver.AddDynamic(this, &ABoardSquare::BeginMouseOver);
		Mesh3->OnEndCursorOver.AddDynamic(this, &ABoardSquare::EndMouseOver);
		Mesh3->OnClicked.AddDynamic(this, &ABoardSquare::SelectSquare);
	}
	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLightComponent"));
	PointLight->SetupAttachment(RootComponent);
	PointLight->SetHiddenInGame(true);
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
	Hide(true, "None");
}

// Called every frame
void ABoardSquare::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABoardSquare::BeginMouseOver(UPrimitiveComponent *TouchedComponent)
{
	if (hidden == false)
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
	if (hidden == false)
	{
		Hide(true, "None");
		AFactionsGameMode *FactionsGameMode = Cast<AFactionsGameMode>(UGameplayStatics::GetGameMode(this));
		APiece *SelectedPiece = FactionsGameMode->GetSelectedPiece();
		FactionsGameMode->FactionsBoard->UnHighlightAllSquares();
		SelectedPiece->MoveToSquare(this);
	} 
	else if (GetOccupyingPiece() != nullptr) 
	{
		GetOccupyingPiece()->PieceSelected();
	}
}

void ABoardSquare::Hide(bool tf, FString color)
{
	if(tf) {
		Mesh1->SetVisibility(false);
		Mesh2->SetVisibility(false);
		Mesh3->SetVisibility(false);
		hidden = true;
	} else if (color == "green") {
		Mesh1->SetVisibility(true);
		hidden = false;
	} else if (color == "blue") {
		Mesh2->SetVisibility(true);
		hidden = false;
	} else if (color == "red") {
		Mesh3->SetVisibility(true);
		hidden = false;
	}
}

void ABoardSquare::SetOccupyingPiece(APiece* piece)
{
	OccupyingPiece = piece;
}

TTuple<int, int> ABoardSquare::GetCoordinates()
{
	return MakeTuple(rank, file);
}

APiece* ABoardSquare::GetOccupyingPiece()
{
	return OccupyingPiece;
}