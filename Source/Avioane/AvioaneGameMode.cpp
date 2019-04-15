#include "AvioaneGameMode.h"
#include "AvioanePlayerController.h"
#include "AvioaneBlockGrid.h"
#include "AvioaneBlock.h"
#include "AvioanePawn.h"
#include "AIPawn.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
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
			gride.Add(*it);
	}
	for (TActorIterator<AAvioaneBlockGrid> it(GetWorld()); it; ++it)
	{
		if (it->ActorHasTag("Copie_Inamic"))
			gride.Add(*it);
	}
	for (int32 i = 0; i < Jucatori.Num(); i++)
	{
		Jucatori[i]->nr_jucator = i;
	}
	Jucator_Actual = 0;
	Jucatori[0]->Plasare_Avioane();
	Jucatori[1]->Plasare_Avioane();
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
			patrat = gride[nr_juc]->tabla[i][j];
			patrat->nr_culoare = k;
			patrat->tip = Jucatori[nr_juc]->acces->tabla[i][j]->tip;
		}
	}
}

bool AAvioaneGameMode::Safe(AAvioaneBlock* patrat)
{
	if (Stadiu == 2 && patrat->ocupat == false && ((patrat->acces->ActorHasTag("Copie_Jucator") && Jucator_Actual == 1) || (patrat->acces->ActorHasTag("Copie_Inamic") && Jucator_Actual == 0)))
		return true;
	else return false;
}

bool AAvioaneGameMode::Lovitura(AAvioaneBlock * patrat)
{
	if (Safe(patrat))
	{
		int32 lin = patrat->lin;
		int32 coln = patrat->coln;

		if (patrat->nr_culoare == -1)
		{
			patrat->BlockMesh->SetMaterial(0, patrat->materiale[1]);
			Jucatori[(Jucator_Actual + 1) % 2]->acces->tabla[lin][coln]->BlockMesh->SetMaterial(0, patrat->materiale[1]);
		}
		else
		{
			patrat->BlockMesh->SetMaterial(0, patrat->materiale[0]);
			Jucatori[(Jucator_Actual + 1) % 2]->acces->tabla[lin][coln]->BlockMesh->SetMaterial(0, patrat->materiale[0]);
			Jucatori[Jucator_Actual]->lovituri[patrat->nr_culoare]++;

			if (patrat->tip == "Mare" && Jucatori[Jucator_Actual]->lovituri[patrat->nr_culoare] == 24)
			{
				Jucatori[Jucator_Actual]->nr_avioane_distruse++;
				Final();
			}
			else if (patrat->tip == "Mic" && Jucatori[Jucator_Actual]->lovituri[patrat->nr_culoare] == 13)
			{
				Jucatori[Jucator_Actual]->nr_avioane_distruse++;
				Final();
			}
		}
		patrat->ocupat = true;	
		Schimb_Jucator();
		return true;
	}
	else
		return false;
}

void AAvioaneGameMode::Schimb_Jucator()
{
	Jucator_Actual = (Jucator_Actual + 1) % 2;
	Jucatori[Jucator_Actual]->Tura();
}

void AAvioaneGameMode::Final()
{
	if (Jucatori[Jucator_Actual]->nr_avioane_distruse == 4)
	{
		GEngine->AddOnScreenDebugMessage(1, 10.f, FColor::Blue, TEXT("GATAA!!!! Lincoln e mare!!"), 1, FVector2D(3, 1));
		Stadiu = 3;
	}
}