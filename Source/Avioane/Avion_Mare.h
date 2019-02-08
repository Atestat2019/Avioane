// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AvioanePawn.h"
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
		class AAvioaneBlock* obiect_atins;

	UPROPERTY(EditAnywhere)
		float val_rot;
	
	UFUNCTION()
		void Rotire_Mare();

	UFUNCTION()
		void Click_Mare(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	class AAvioanePawn* blabla;

	bool selectat_mare;

protected:
	// Begin AActor interface
	
	virtual void BeginPlay() override;
	void Tick(float DeltaTime);
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnOverlapExit(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	// End AActor interface

};