// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Avion_Mare.generated.h"

UCLASS()
class AVIOANE_API AAvion_Mare : public AActor
{
	GENERATED_BODY()


public:
	AAvion_Mare();

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere)
		float val_rot;

protected:
	// Begin AActor interface
	UFUNCTION()
	void Rotire(UPrimitiveComponent * ClickedComp, FKey ButtonClicked);
	virtual void BeginPlay() override;
	void Tick(float DeltaTime);
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	// End AActor interface

};