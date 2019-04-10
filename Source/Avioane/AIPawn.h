// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerInstance.h"
#include "GameFramework/Pawn.h"
#include "AIPawn.generated.h"

UCLASS()
class AVIOANE_API AAIPawn : public APawn, public PlayerInstance
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAIPawn();

	UFUNCTION()
		virtual void Plasare_Avioane() override;

	UFUNCTION()
		virtual void intarziere() override;

	class AAvioaneBlockGrid* acces_AI;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
