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
	MoveCaptureMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MoveCaptureMesh"));
	if (MoveCaptureMesh)
	{
		MoveCaptureMesh->SetupAttachment(RootComponent);
		MoveCaptureMesh->OnBeginCursorOver.AddDynamic(this, &ABoardSquare::BeginMouseOver);
		MoveCaptureMesh->OnEndCursorOver.AddDynamic(this, &ABoardSquare::EndMouseOver);
		MoveCaptureMesh->OnClicked.AddDynamic(this, &ABoardSquare::SelectSquare);
	}
	SpecialMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpecialMesh"));
	if (SpecialMesh)
	{
		SpecialMesh->SetupAttachment(RootComponent);
		SpecialMesh->OnBeginCursorOver.AddDynamic(this, &ABoardSquare::BeginMouseOver);
		SpecialMesh->OnEndCursorOver.AddDynamic(this, &ABoardSquare::EndMouseOver);
		SpecialMesh->OnClicked.AddDynamic(this, &ABoardSquare::SelectSquare);
	}
	RemoteCaptureMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RemoteCaptureMesh"));
	if (RemoteCaptureMesh)
	{
		RemoteCaptureMesh->SetupAttachment(RootComponent);
		RemoteCaptureMesh->OnBeginCursorOver.AddDynamic(this, &ABoardSquare::BeginMouseOver);
		RemoteCaptureMesh->OnEndCursorOver.AddDynamic(this, &ABoardSquare::EndMouseOver);
		RemoteCaptureMesh->OnClicked.AddDynamic(this, &ABoardSquare::SelectSquare);
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
	Hide(true, FColor::Transparent);
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
		AFactionsGameMode *FactionsGameMode = Cast<AFactionsGameMode>(UGameplayStatics::GetGameMode(this));
		APiece *SelectedPiece = FactionsGameMode->GetSelectedPiece();
		if (MoveCaptureMesh->IsVisible())
			SelectedPiece->MoveToSquare(this);
		else if (SpecialMesh->IsVisible())
			SelectedPiece->PerformSpecial(this);
		else if (RemoteCaptureMesh->IsVisible())
		{
			GetOccupyingPiece()->Destroy();
			SetOccupyingPiece(nullptr);
		}
		Hide(true, FColor::Transparent);
		FactionsGameMode->FactionsBoard->UnHighlightAllSquares();
		FactionsGameMode->StartNextTurn();
	} 
	else if (GetOccupyingPiece() != nullptr) 
	{
		GetOccupyingPiece()->PieceSelected();
	}
}

void ABoardSquare::Hide(bool tf, FColor color)
{
	if(tf) {
		MoveCaptureMesh->SetVisibility(false);
		SpecialMesh->SetVisibility(false);
		RemoteCaptureMesh->SetVisibility(false);
		hidden = true;
	} else if (color == FColor::Green) {
		MoveCaptureMesh->SetVisibility(true);
		hidden = false;
	} else if (color == FColor::Blue) {
		SpecialMesh->SetVisibility(true);
		hidden = false;
	} else if (color == FColor::Red) {
		RemoteCaptureMesh->SetVisibility(true);
		hidden = false;
	}
}

void ABoardSquare::SetBlockAllButColor(FColor BlockColor)
{
	BlockAllButColor = BlockColor;
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

FColor ABoardSquare::GetBlockAllButColor()
{
	return BlockAllButColor;
}