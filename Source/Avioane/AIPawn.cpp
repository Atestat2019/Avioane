#include "AIPawn.h"
#include "EngineUtils.h"
#include "AvioaneBlockGrid.h"
#include "AvioaneGameMode.h"
#include "AvioaneBlock.h"
#include "Engine/Engine.h"
#include "Engine/Public/TimerManager.h"

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
}

void AAIPawn::Plasare_Avioane()
{
	GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Blue, TEXT("Calculatorul isi plaseaza avioanele"));
	//GM->Colorare_Tabla(1);
}

void AAIPawn::intarziere()
{
	int32 n, m, r;

	for (int32 i = 0; i < acces->avioane.Num(); i++)
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

	GM->Colorare_Tabla(1);

	GetWorldTimerManager().ClearTimer(chronos);
}

void AAIPawn::Tura()
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Orange, TEXT("Este tura AI-ului!"));
	int32 i = FMath::RandRange(0, 19);
	int32 j = FMath::RandRange(0, 19);
	while (GM->Lovitura(GM->gride[0]->tabla[i][j]) == false)
	{
		i = FMath::RandRange(0, 19);
		j = FMath::RandRange(0, 19);
	}
}

void AAIPawn::BeginPlay()
{
	Super::BeginPlay();

	GM = GetWorld()->GetAuthGameMode<AAvioaneGameMode>();
	
	for (TActorIterator<AAvioaneBlockGrid> it(GetWorld()); it; ++it)
	{
		if (it->ActorHasTag("Inamic"))
			acces = *it;
	}

	GetWorld()->GetTimerManager().SetTimer(chronos, this, &AAIPawn::intarziere, 0.2f, false);
	
	
}

void AAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}