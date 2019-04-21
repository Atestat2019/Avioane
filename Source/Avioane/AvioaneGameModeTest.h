// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AvioaneGameMode.h"
#include "AvioaneGameModeTest.generated.h"

/**
 * 
 */
UCLASS()
class AVIOANE_API AAvioaneGameModeTest : public AAvioaneGameMode
{
	GENERATED_BODY()
		
	virtual bool Safe(AAvioaneBlock* patrat) override;

	virtual void Colorare_Tabla(int32 nr_juc) override;

	virtual bool Lovitura(AAvioaneBlock* patrat) override;

	virtual void Schimb_Jucator() override;

	virtual void Doborare_Avion(int32 k) override;

	virtual void Final() override;
};
