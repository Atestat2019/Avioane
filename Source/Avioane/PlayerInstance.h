// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class AVIOANE_API PlayerInstance
{
public:

	int32 nr_jucator;

	int32 nr_avioane_distruse;
	
	int32 lovituri[15];

	class AAvioaneBlockGrid* acces;

	virtual void Plasare_Avioane() {};
	virtual void intarziere() {};
	virtual void Tura() {};
};
