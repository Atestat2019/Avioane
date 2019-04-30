// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerInstance.h"
#include "GameFramework/Pawn.h"
#include "AIPawn.generated.h"

struct lovitura
{
	int32 i_lovit;
	int32 j_lovit;
};

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

	UFUNCTION()
		virtual void Tura() override;
	
	UPROPERTY(EditAnywhere)
		int32 nr_tura;

	UPROPERTY(EditAnywhere)
		int32 caz;

	TArray<lovitura> lovituri;

	class AAvioaneGameMode* GM;

	FTimerHandle chronos2;


protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

};
