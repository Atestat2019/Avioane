// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Avion_Mic.generated.h"

UCLASS()
class AVIOANE_API AAvion_Mic : public AActor
{
	GENERATED_BODY()


public:
	
	AAvion_Mic();

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere)
		float val_rot;



protected:
	
	UFUNCTION()
	void Rotire(UPrimitiveComponent * ClickedComp, FKey ButtonClicked);
	// Begin AActor interface
	virtual void BeginPlay() override;
	void Tick(float DeltaTime);
	// End AActor interface



};
