// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class AVIOANE_API PlayerInstance
{
public:

	int32 nr_jucator;

	int32 nr_avioane_distruse;

	/*  ~~~~ Primul mod de joc
	int32 lovituri[15] = { 0 };
	*/

	int32 piloti_doborati[20];
	
	int32 motoare_distruse[20];

	FTimerHandle chronos;

	class AAvioaneBlockGrid* acces;

	class AAvioaneBlockGrid* grida;

	virtual void Plasare_Avioane() {};
	virtual void intarziere() {};
	virtual void Tura() {};
	virtual void Ref() {};
};
