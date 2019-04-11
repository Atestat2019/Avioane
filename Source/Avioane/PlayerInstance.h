// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class AVIOANE_API PlayerInstance
{
public:

	int32 nr_jucator;

	class AAvioaneBlockGrid* acces;

	virtual void Plasare_Avioane() {};
	virtual void intarziere() {};
};
