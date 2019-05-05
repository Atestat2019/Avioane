#include "AIPawn.h"
#include "EngineUtils.h"
#include "AvioaneBlockGrid.h"
#include "AvioaneGameMode.h"
#include "AvioaneBlock.h"
#include "Engine/Engine.h"
#include "Engine/Public/TimerManager.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"

AAIPawn::AAIPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	acces = nullptr;
	nr_jucator = 1;
	nr_avioane_distruse = 0;

	for (int32 i = 0; i < 20; i++)
		motoare_distruse[i] = 0;

	for (int32 i = 0; i < 20; i++)
		piloti_doborati[i] = 0;

	nr_tura = 0;
	caz = 0;
	acces = nullptr;
}

void AAIPawn::Plasare_Avioane()
{
	if (nr_jucator == 1)
		GetWorld()->GetTimerManager().SetTimer(chronos, this, &AAIPawn::intarziere, 1.0f, false);
	else GetWorld()->GetTimerManager().SetTimer(chronos, this, &AAIPawn::intarziere, 3.0f, false);
}

void AAIPawn::intarziere()
{
	int32 n, m, r;
	
	for (int32 i = 0; i < 4; i++)
	{
		n = FMath::RandRange(2, 17);
		m = FMath::RandRange(2, 17);
		r = FMath::RandRange(0, 3);

		acces->avioane[i]->Click(nullptr, "null");

		for (int32 j = 1; j <= r; j++)
		{
			acces->avioane[i]->Rotire();
		}
		acces->tabla[n][m]->Evidentiere(true);

		while ((i == 0 && acces->avioane[i]->nr != 24) || (i > 0 && acces->avioane[i]->nr != 13))
		{
			n = FMath::RandRange(2, 17);
			m = FMath::RandRange(2, 17);
			acces->tabla[n][m]->Evidentiere(true);
		}
		acces->tabla[n][m]->HandleClicked(nullptr, "null");
	}

	GM->Copiere_Tabla(nr_jucator);
	
	GetWorldTimerManager().ClearTimer(chronos);
}

void AAIPawn::Tura()
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Orange, TEXT("Este tura AI-ului!"));

					//     Prima dificultate  +++ variabila dificultate
	/*
	int32 i = FMath::RandRange(0, 19);
	int32 j = FMath::RandRange(0, 19);
	while (GM->Lovitura(GM->gride[(nr_jucator+1)%2]->tabla[i][j]) == false)
	{
		i = FMath::RandRange(0, 19);
		j = FMath::RandRange(0, 19);
	}
	*/
	

	nr_tura++;
	UE_LOG(LogTemp, Warning, TEXT("ture %d"), nr_tura);

	int32 verif_distruse = nr_avioane_distruse;
	int32 i;
	int32 j;
	int32 i_urm;
	int32 j_urm;
	int32 dir;
	lovitura l;

	int dir_i[] = { 1,0,-1,0 }, dir_j[] = { 0,1,0,-1 };

	if (lovituri.Num() != 0)
	{
		bool ok = false;

		while (ok == false)
		{
			if (lovituri.Num() != 0)
			{
				l = lovituri.Last();

					for (dir = 0; dir < 4; dir++)
					{
						if (caz == 1)
						{
							i_urm = l.i_lovit + 2 * dir_i[dir];
							j_urm = l.j_lovit + 2 * dir_j[dir];
						}
						else if (caz == 2)
						{
							i_urm = l.i_lovit + 5 * dir_i[dir];
							j_urm = l.j_lovit + 5 * dir_j[dir];
						}
						else
						{
							i_urm = l.i_lovit + dir_i[dir];
							j_urm = l.j_lovit + dir_j[dir];
						}
						if (GM->safe_margine(i_urm, j_urm) == true && GM->gride[(nr_jucator + 1) % 2]->tabla[i_urm][j_urm]->ocupat == false)
							ok = true;
					}
					if (ok == false)
					{
						if (caz == 0)
						{
							lovituri.Pop();
						}
						else
						{
							caz = (caz + 1) % 4;
						}
					}
				
			}
			else ok = true;
		}
	}
	if (lovituri.Num() == 0)
	{
		i = FMath::RandRange(2, 17);
		j = FMath::RandRange(2, 17);
		
		int ok_liber = true;
	
		for (dir = 0; dir < 4; dir++)
		{
			i_urm = i + dir_i[dir];
			j_urm = j + dir_j[dir];

			if (GM->safe_margine(i_urm, j_urm) == true)
			{	
				if (GM->gride[(nr_jucator+1)%2]->tabla[i_urm][j_urm]->ocupat == true)
					ok_liber = false;
			}
		}
		while (GM->Safe(GM->gride[(nr_jucator + 1) % 2]->tabla[i][j],ok_liber) == false)
		{
			ok_liber = true;

			//UE_LOG(LogTemp, Warning, TEXT("a incercat la %d, %d"), i, j);
			
			i = FMath::RandRange(2, 17);
			j = FMath::RandRange(2, 17);

			for (dir = 0; dir < 4; dir++)
			{
				i_urm = i + dir_i[dir];
				j_urm = j + dir_j[dir];
				
				if (GM->safe_margine(i_urm, j_urm) == true)
				{	
					if (GM->gride[(nr_jucator+1)%2]->tabla[i_urm][j_urm]->ocupat == true)
						ok_liber = false;
				}
			}
		}
		GM->Lovitura(GM->gride[(nr_jucator + 1) % 2]->tabla[i][j]);
		//UE_LOG(LogTemp, Warning, TEXT("a reusit la %d, %d"), i, j);
		if (GM->gride[(nr_jucator+1)%2]->tabla[i][j]->nr_culoare != -1)
		{
			lovituri.Add({ i, j });
		}
	}
	else
	{
		l = lovituri.Last();

		dir=FMath::RandRange(0, 3);

		if (GM->gride[(nr_jucator+1)%2]->tabla[l.i_lovit][l.j_lovit]->BlockMesh->GetMaterial(0) == GM->gride[(nr_jucator+1)%2]->tabla[l.i_lovit][l.j_lovit]->materiale[0] && (caz == 0 || caz == 1))
		{
			i_urm = l.i_lovit + 2*dir_i[dir];
			j_urm = l.j_lovit + 2*dir_j[dir];
			caz = 1;
		}
		else if (caz == 2)
		{
			i_urm = l.i_lovit + 5 * dir_i[dir];
			j_urm = l.j_lovit + 5 * dir_j[dir];
		}
		else
		{
			i_urm = l.i_lovit + dir_i[dir];
			j_urm = l.j_lovit + dir_j[dir];
		}
		while (GM->safe_margine(i_urm, j_urm) == false || GM->Lovitura(GM->gride[(nr_jucator+1)%2]->tabla[i_urm][j_urm]) == false)
		{
			dir = FMath::RandRange(0, 3);

			if (caz == 1)
			{
				i_urm = l.i_lovit + 2 * dir_i[dir];
				j_urm = l.j_lovit + 2 * dir_j[dir];
			}
			else if (caz == 2)
			{
				i_urm = l.i_lovit + 5 * dir_i[dir];
				j_urm = l.j_lovit + 5 * dir_j[dir];
			}
			else
			{
				i_urm = l.i_lovit + dir_i[dir];
				j_urm = l.j_lovit + dir_j[dir];
			}
		}
		if (GM->gride[(nr_jucator+1)%2]->tabla[i_urm][j_urm]->nr_culoare != -1)
		{
			if (nr_avioane_distruse != verif_distruse)
			{
				for (int32 lin = 0; lin < 20; lin++)
				{
					for (int32 coln = 0; coln < 20; coln++)
					{
						if (GM->gride[(nr_jucator+1)%2]->tabla[lin][coln]->BlockMesh->GetMaterial(0) == GM->gride[(nr_jucator+1)%2]->tabla[lin][coln]->materiale[0])
						{
							for (int32 k = 0; k < lovituri.Num(); k++)
							{
								if (lovituri[k].i_lovit == lin && lovituri[k].j_lovit == coln)
								{
									lovituri.RemoveAt(k);
								}
							}
						}
					}
				}
				caz = 0; 
			}
			else if (caz == 0)
			{	
				lovituri.Add({i_urm, j_urm});
			}
			else
			{
				lovituri.Insert({ i_urm,j_urm }, 0);
			}
		}
	}
}

void AAIPawn::Ref()
{
	GM = GetWorld()->GetAuthGameMode<AAvioaneGameMode>();

	for (TActorIterator<AAvioaneBlockGrid> it(GetWorld()); it; ++it)
	{
		if (it->ActorHasTag("Inamic") && nr_jucator == 1)
			acces = *it;
		else if (it->ActorHasTag("Jucator") && nr_jucator == 0)
			acces = *it;
	}
}

void AAIPawn::BeginPlay()
{
	Super::BeginPlay();
}

void AAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}