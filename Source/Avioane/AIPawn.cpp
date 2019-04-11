#include "AIPawn.h"
#include "EngineUtils.h"
#include "AvioaneBlockGrid.h"
#include "AvioaneGameMode.h"
#include "AvioaneBlock.h"
#include "Engine/Engine.h"

AAIPawn::AAIPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	acces = nullptr;
	nr_jucator = 1;
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
			acces = *it;
	}

	int32 n, m, r;
		
	for (int32 i = 0; i < 4; i++)
	{
		n = FMath::RandRange(2, 17);
		m = FMath::RandRange(2, 17);
		r = FMath::RandRange(0, 3);
		acces->avioane[i]->Click(nullptr, "null");

		for (int32 j=1;j<=r;j++)
		{ 
			acces->avioane[i]->Rotire();
		}
		acces->tabla[n][m]->Evidentiere(true);

		while ((i==0 && acces->avioane[i]->nr!=24) || (i>0 && acces->avioane[i]->nr != 13))
		{
			n = FMath::RandRange(2, 17);
			m = FMath::RandRange(2, 17);
			acces->tabla[n][m]->Evidentiere(true);
		}
		acces->tabla[n][m]->HandleClicked(nullptr, "null");	
	}

	AAvioaneGameMode* GM = GetWorld()->GetAuthGameMode<AAvioaneGameMode>();
	GM->Colorare_Tabla(nr_jucator);
}

void AAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}