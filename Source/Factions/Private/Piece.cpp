// Fill out your copyright notice in the Description page of Project Settings.


#include "Piece.h"
#include "FactionsBoard.h"
#include "FactionsGameMode.h"
#include "Components/CapsuleComponent.h"
#include "kismet/GameplayStatics.h"

// Sets default values
APiece::APiece()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UCapsuleComponent* CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RootComponent"));
    RootComponent = CapsuleComponent;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	if(BaseMesh) {
		BaseMesh->SetupAttachment(RootComponent);
		BaseMesh->OnBeginCursorOver.AddDynamic(this, &APiece::BeginMouseOver);
		BaseMesh->OnClicked.AddDynamic(this, &APiece::PieceSelected);
	}
}

// Called when the game starts or when spawned
void APiece::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void APiece::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APiece::EndMouseOver(UPrimitiveComponent *TouchedComponent) {}

void APiece::BeginMouseOver(UPrimitiveComponent *TouchedComponent) {

}

void APiece::PieceSelected(UPrimitiveComponent *TouchedComponent, FKey InKey) {
	FString Name = GetName();
	UE_LOG(LogTemp , Display, TEXT("%s selected"), *Name);
	AFactionsGameMode* FactionsGameMode = Cast<AFactionsGameMode>(UGameplayStatics::GetGameMode(this));
	if(!IsValid(FactionsGameMode)) {
		UE_LOG(LogTemp , Display, TEXT("FactionsGameMode not valid"), *Name);
	}
	if(!IsValid(FactionsGameMode->FactionsBoard)) {
		UE_LOG(LogTemp , Display, TEXT("FactionsBoard not valid"), *Name);
	}
	FactionsGameMode->FactionsBoard->HighlightSquares(MovesX, MovesY, BoardPosition);
	FactionsGameMode->SetSelectedPiece(this);
	FVector CurrentLocation = GetActorLocation();
	SetActorLocation(CurrentLocation + RaiseHeight);
}
