// Fill out your copyright notice in the Description page of Project Settings.


#include "Piece.h"
#include "Components/CapsuleComponent.h"

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
