#include "AvioaneGameMode.h"
#include "AvioanePlayerController.h"
#include "AvioaneBlockGrid.h"
#include "AvioaneBlock.h"
#include "AvioanePawn.h"
#include "AIPawn.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"


AAvioaneGameMode::AAvioaneGameMode()
{
	DefaultPawnClass = AAvioanePawn::StaticClass();
	PlayerControllerClass = AAvioanePlayerController::StaticClass();

	Stadiu = 1;
}


bool AAvioaneGameMode::Safe(AAvioaneBlock* patrat)
{
	if (Stadiu == 2 && (patrat->acces->ActorHasTag("Copie_Jucator") || patrat->acces->ActorHasTag("Copie_Inamic")))
		return true;
	
	return false;
}


void AAvioaneGameMode::Colorare_Tabla(int32 nr_juc)
{
	int32 k;
	AAvioaneBlock* patrat;
	for (int32 i = 0; i < 20; i++)
	{
		for (int32 j = 0; j < 20; j++)
		{
			k = Jucatori[nr_juc]->acces->tabla[i][j]->nr_culoare;
			patrat = table[nr_juc]->tabla[i][j];
			patrat->nr_culoare = k;
			/*
			if (k!=-1)
				patrat->BlockMesh->SetMaterial(0, patrat->materiale[k % 4]);
			*/
		}
	}
}

void AAvioaneGameMode::BeginPlay()
{
	Super::BeginPlay();


	for (TActorIterator<AAvioanePawn> it(GetWorld()); it; ++it)
	{
		Jucatori.Add(*it);
		break;
	}
	for (TActorIterator<AAIPawn> it(GetWorld()); it; ++it)
	{
		Jucatori.Add(*it);
		break;
	}

	for (TActorIterator<AAvioaneBlockGrid> it(GetWorld()); it; ++it)
	{
		if (it->ActorHasTag("Copie_Jucator"))
			table.Add(*it);
	}
	for (TActorIterator<AAvioaneBlockGrid> it(GetWorld()); it; ++it)
	{
		if (it->ActorHasTag("Copie_Inamic"))
			table.Add(*it);
	}

	for (int32 i = 0; i < Jucatori.Num(); i++)
	{
		Jucatori[i]->nr_jucator = i;
	}
	Jucator_Actual = 0;
	Jucatori[Jucator_Actual]->Plasare_Avioane();
	Jucatori[(Jucator_Actual+1)%Jucatori.Num()]->Plasare_Avioane();

	
}

