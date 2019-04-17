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
#include "Engine/Public/TimerManager.h"


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
			patrat->pilot = Jucatori[nr_juc]->acces->tabla[i][j]->pilot;
			patrat->motor = Jucatori[nr_juc]->acces->tabla[i][j]->motor;
		}
	}
}

bool AAvioaneGameMode::Safe(AAvioaneBlock* patrat)
{
	if (Stadiu == 2 && patrat->ocupat == false && ((patrat->acces->ActorHasTag("Copie_Jucator") && Jucator_Actual == 1) || (patrat->acces->ActorHasTag("Copie_Inamic") && Jucator_Actual == 0)))
		return true;
	else return false;
}

void AAvioaneGameMode::Doborare_Avion(int32 k)
{
	AAvioaneBlock* patrat1;
	AAvioaneBlock* patrat2;

	for (int32 i = 0; i < 20; i++)
	{
		for (int32 j = 0; j < 20; j++)
		{
			patrat1 = gride[(Jucator_Actual + 1) % 2]->tabla[i][j];
			patrat2 = Jucatori[(Jucator_Actual + 1) % 2]->acces->tabla[i][j];

			if (patrat1->nr_culoare == k)
			{
				patrat1->BlockMesh->SetMaterial(0, patrat1->materiale[0]);
				patrat2->BlockMesh->SetMaterial(0, patrat2->materiale[0]);
				patrat1->ocupat = true;
			}
		}
	}
	Jucatori[Jucator_Actual]->nr_avioane_distruse++;
	Final();
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

			int32 nr_culoare = patrat->nr_culoare;
			Jucatori[(Jucator_Actual + 1) % 2]->acces->tabla[lin][coln]->BlockMesh->SetMaterial(0, patrat->materiale[0]);

			/*   ~~~~ Primul mod de joc
			Jucatori[Jucator_Actual]->lovituri[nr_culoare]++;

			if (patrat->tip == "Mare" && Jucatori[Jucator_Actual]->lovituri[nr_culoare] == 24)
			{
				Jucatori[Jucator_Actual]->nr_avioane_distruse++;											
				Final();
			}
			else if (patrat->tip == "Mic" && Jucatori[Jucator_Actual]->lovituri[nr_culoare] == 13)
			{
				Jucatori[Jucator_Actual]->nr_avioane_distruse++;
				Final();
			}
			*/

			if (patrat->tip == "Mare")
			{
				if (patrat->pilot == true)
				{
					Jucatori[Jucator_Actual]->piloti_doborati[nr_culoare]++;
					//mesaj
					if (Jucatori[Jucator_Actual]->piloti_doborati[nr_culoare] == 2)
					{
						Doborare_Avion(nr_culoare);
					}
				}
				else if (patrat->motor == true)
				{
					Jucatori[Jucator_Actual]->motoare_distruse[nr_culoare]++;
					//mesaj
					if (Jucatori[Jucator_Actual]->motoare_distruse[nr_culoare] == 2)
					{
						Doborare_Avion(nr_culoare);
					}
				}
			}
			else
			{
				if (patrat->pilot == true)
				{
					Doborare_Avion(nr_culoare);
				}
				else if (patrat->motor == true)
				{
					Jucatori[Jucator_Actual]->motoare_distruse[nr_culoare]++;
					//mesaj
					if (Jucatori[Jucator_Actual]->motoare_distruse[nr_culoare] == 2)
					{
						Doborare_Avion(nr_culoare);
					}
				}
			}
		}
		patrat->ocupat = true;
		Schimb_Jucator();
		//GetWorld()->GetTimerManager().SetTimer(chronos, this, &AAvioaneGameMode::Schimb_Jucator, 20, false);
		return true;
	}
	else
		return false;
}

void AAvioaneGameMode::Schimb_Jucator()
{
	Jucator_Actual = (Jucator_Actual + 1) % 2;
	Jucatori[Jucator_Actual]->Tura();
	//GetWorldTimerManager().ClearTimer(chronos);
}

void AAvioaneGameMode::Final()
{
	if (Jucatori[Jucator_Actual]->nr_avioane_distruse == 4)
	{
		GEngine->AddOnScreenDebugMessage(1, 10.f, FColor::Blue, TEXT("GATAA!!!! Lincoln e mare!!"), 1, FVector2D(3, 1));
		//Stadiu = 3;
	}
}