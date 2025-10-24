// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FactionsCharacter.generated.h"

class USkeletalMeshComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputComponent;
struct FInputActionValue;

UCLASS()
class FACTIONS_API AFactionsCharacter : public ACharacter
{
	GENERATED_BODY()

		/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

public:
	// Sets default values for this character's properties
	AFactionsCharacter();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void Look(const FInputActionValue& Value);
	virtual void NotifyControllerChanged() override;
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	UPROPERTY(ReplicatedUsing = OnRep_PlayerColor) 
	FColor PlayerColor;
	 
	UFUNCTION()
	void OnRep_PlayerColor();

	void OnPlayerColorUpdate();

	UPROPERTY(ReplicatedUsing = OnRep_MyTurn)
	bool MyTurn;

	UFUNCTION()
	void OnRep_MyTurn();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool IsMyTurn();

	void SetMyTurn(bool MyTurn);

	void SetColor(FColor Color);
	
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	FColor GetColor() const { return PlayerColor; }

};
