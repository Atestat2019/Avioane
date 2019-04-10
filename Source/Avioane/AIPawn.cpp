#include "AIPawn.h"
#include "EngineUtils.h"
#include "AvioaneBlockGrid.h"
#include "AvioaneGameMode.h"
#include "AvioaneBlock.h"
#include "Engine.h"

AAIPawn::AAIPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	acces_AI = nullptr;
}

void AAIPawn::Plasare_Avioane()
{
	GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Blue, TEXT("Calculatorul isi plaseaza avioanele"));
}

void AAIPawn::intarziere()
{

}

void AAIPawn::BeginPlay()
{
	Super::BeginPlay();
	
	for (TActorIterator<AAvioaneBlockGrid> it(GetWorld()); it; ++it)
	{
		if (it->ActorHasTag("Inamic"))
			acces_AI = *it;
	}

	int32 n, m, r;
		
	for (int32 i = 0; i < 4; i++)
	{
		n = FMath::RandRange(2, 17);
		m = FMath::RandRange(2, 17);
		r = FMath::RandRange(0, 3);
		acces_AI->avioane[i]->Click(nullptr, "null");

		for (int32 j=1;j<=r;j++)
		{ 
			acces_AI->avioane[i]->Rotire();
		}
		acces_AI->tabla[n][m]->Evidentiere(true);

		while ((i==0 && acces_AI->avioane[i]->nr!=24) || (i>0 && acces_AI->avioane[i]->nr != 13))
		{
			n = FMath::RandRange(2, 17);
			m = FMath::RandRange(2, 17);
			acces_AI->tabla[n][m]->Evidentiere(true);
		}
		acces_AI->tabla[n][m]->HandleClicked(nullptr, "null");	
	}
}

void AAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}