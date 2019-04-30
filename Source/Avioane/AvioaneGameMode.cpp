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
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Core/Public/Misc/FileHelper.h"
#include "Core/Public/Misc/Paths.h"
#include "Engine/Classes/Sound/AmbientSound.h"

// https://midi.city/

AAvioaneGameMode::AAvioaneGameMode()
{
	DefaultPawnClass = AAvioanePawn::StaticClass();
	PlayerControllerClass = AAvioanePlayerController::StaticClass();

	Stadiu = 1;
	ok = 0;

	mod_de_joc = "0";
}

void AAvioaneGameMode::BeginPlay()
{
	Super::BeginPlay();

	FString SaveTextA;

	FFileHelper::LoadFileToString(SaveTextA, *(FPaths::GameDir() + "Mod_de_Joc.txt"));

	mod_de_joc = SaveTextA;

	if (mod_de_joc != "0" && mod_de_joc != "1")
	{
		mod_de_joc = "0";
	}

	if (mod_de_joc == "1")
	{
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
	}
	else
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);

		PC->bEnableClickEvents = false;
		PC->bEnableMouseOverEvents = false;

		for (TActorIterator<AAIPawn> it(GetWorld()); it; ++it)
		{
			Jucatori.Add(*it);
			break;
		}
		Jucatori.Add(GetWorld()->SpawnActor<AAIPawn>(FVector(0, 0, 0), FRotator(0, 0, 0)));
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
	int32 k=0;
	AAvioaneBlock* patrat=nullptr;

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

bool AAvioaneGameMode::Safe(AAvioaneBlock* patrat, int32 ok_liber)
{
	if (Stadiu == 2 && patrat->ocupat == false && ((patrat->acces->ActorHasTag("Copie_Jucator") && Jucator_Actual == 1) || (patrat->acces->ActorHasTag("Copie_Inamic") && Jucator_Actual == 0)))
	{
		if (ok_liber == 1)
			return true;
		else return false;
	}
	else return false;
}

bool AAvioaneGameMode::safe_margine(int32 i, int32 j)
{
	if (i < 0 || i>19 || j < 0 || j>19)
		return false;
	else return true;
}

void AAvioaneGameMode::Doborare_Avion(int32 k)
{
	Jucatori[1]->acces->sunet->Play();
	
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
				if (Jucator_Actual == 1 || mod_de_joc == "0")
				{
					int dir_i[] = { 1,0,-1,0 }, dir_j[] = { 0,1,0,-1 };
					for (int32 dir = 0; dir < 4; dir++)
					{
						if (safe_margine(i + dir_i[dir], j + dir_j[dir]) == true)
						{
							gride[(Jucator_Actual + 1) % 2]->tabla[i + dir_i[dir]][j + dir_j[dir]]->ocupat = true;
						}
					}
				}
				patrat1->BlockMesh->SetMaterial(0, patrat1->materiale[0]);
				patrat2->BlockMesh->SetMaterial(0, patrat2->X_materiale[patrat2->nr_culoare-1]);
				patrat1->ocupat = true;
			}
		}
	}
	Jucatori[Jucator_Actual]->nr_avioane_distruse++;
	Final();
}

bool AAvioaneGameMode::Lovitura(AAvioaneBlock * patrat)
{
	if (Safe(patrat,1))
	{
		gride[(Jucator_Actual + 1) % 2]->sunet->Play();
		
		int32 lin = patrat->lin;
		int32 coln = patrat->coln;

		if (patrat->nr_culoare == -1)
		{
			patrat->BlockMesh->SetMaterial(0, patrat->Material_0);
			Jucatori[(Jucator_Actual + 1) % 2]->acces->tabla[lin][coln]->BlockMesh->SetMaterial(0, patrat->Material_0);
		}
		else
		{
			patrat->BlockMesh->SetMaterial(0, patrat->XGriMaterial);

			int32 nr_culoare = patrat->nr_culoare;
			Jucatori[(Jucator_Actual + 1) % 2]->acces->tabla[lin][coln]->BlockMesh->SetMaterial(0, patrat->X_materiale[nr_culoare-1]);

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
					patrat->BlockMesh->SetMaterial(0, patrat->materiale[0]);
					Jucatori[(Jucator_Actual + 1) % 2]->acces->tabla[lin][coln]->BlockMesh->SetMaterial(0, patrat->materiale[0]);
					//mesaj
					if (Jucatori[Jucator_Actual]->piloti_doborati[nr_culoare] == 2)
					{
						Doborare_Avion(nr_culoare);

					}
				}
				else if (patrat->motor == true)
				{
					Jucatori[Jucator_Actual]->motoare_distruse[nr_culoare]++;
					patrat->BlockMesh->SetMaterial(0, patrat->materiale[0]);
					Jucatori[(Jucator_Actual + 1) % 2]->acces->tabla[lin][coln]->BlockMesh->SetMaterial(0, patrat->materiale[0]);
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
					patrat->BlockMesh->SetMaterial(0, patrat->materiale[0]);
					Jucatori[(Jucator_Actual + 1) % 2]->acces->tabla[lin][coln]->BlockMesh->SetMaterial(0, patrat->materiale[0]);
					//mesaj
					if (Jucatori[Jucator_Actual]->motoare_distruse[nr_culoare] == 2)
					{
						Doborare_Avion(nr_culoare);
					}
				}
			}
		}
		patrat->ocupat = true;
		//  IL SUN PE GHEORGHE // BINE
		if (Stadiu < 3) 
		{
			if (mod_de_joc == "0")
			{
				GetWorldTimerManager().ClearTimer(chronos);
				GetWorld()->GetTimerManager().SetTimer(chronos, this, &AAvioaneGameMode::Schimb_Jucator, FMath::RandRange(0.5f, 1.0f), false);
			}
			else
			{
				APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);

				if (Jucator_Actual == 0)
				{
					PC->bEnableClickEvents = false;
					PC->bEnableMouseOverEvents = false;

					GetWorldTimerManager().ClearTimer(chronos);
					GetWorld()->GetTimerManager().SetTimer(chronos, this, &AAvioaneGameMode::Schimb_Jucator, 0.3f, false);
				}
				else
				{
					PC->bEnableClickEvents = true;
					PC->bEnableMouseOverEvents = true;
					Schimb_Jucator();
				}
			}
		}
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