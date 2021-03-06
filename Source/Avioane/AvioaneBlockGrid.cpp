#include "AvioaneBlockGrid.h"
#include "AvioaneBlock.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"
#include "Components/BoxComponent.h"
#include "EngineUtils.h"
#include "Avion.h"
#include "AvioanePawn.h"
#include "Engine/Classes/Sound/AmbientSound.h"
#include "AvioaneGameMode.h"

#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"


AAvioaneBlockGrid::AAvioaneBlockGrid()
{
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	box = CreateDefaultSubobject<UBoxComponent>(TEXT("boxxxx"));
	
	box->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	box->OnBeginCursorOver.AddDynamic(this, &AAvioaneBlockGrid::OnCursorOver);

	RootComponent = DummyRoot;

	nr_cuburi = 20;
	dist = 170.f;
	scala_x = scala_y = 0.6;
	scala_z = 0;

	este_avion_selectat = false;
	merge_pus = false;

	avion_selectat = nullptr;
	contor_avioane = 0;

	for (int32 i = 0; i < 20; i++)
		frecv[i] = 0;

	for (int32 i = 0; i < 21; i++)
	{
		for (int32 j = 0; j < 21; j++)
		{
			tabla[i][j] = nullptr;
		}
	}

	mesaj = CreateDefaultSubobject<UTextRenderComponent>(TEXT("mesaj"));
}

void AAvioaneBlockGrid::OnCursorOver(UPrimitiveComponent * Component)
{
	AAvioaneGameMode* GM = GetWorld()->GetAuthGameMode<AAvioaneGameMode>();
	
	UE_LOG(LogTemp, Warning, TEXT("iNTRA"));

	if (GM->Stadiu == 1 && GM->mod_de_joc=="1" && this->ActorHasTag("Jucator"))
	{
		if (este_avion_selectat == true)
		{
			avion_selectat->SetActorLocation(avion_selectat->locinit);
		}
	}
}

void AAvioaneBlockGrid::BeginPlay()
{
	Super::BeginPlay();
	
	box->SetRelativeLocation({ 1620, 1620, -2 });
	box->SetWorldScale3D({ 10000, 10000, 0 });

	const int32 NumBlocks = nr_cuburi * nr_cuburi;
	int32 nr=0;

	for(int32 i=0; i<nr_cuburi; i++)
	{
		for (int32 j = 0; j < nr_cuburi; j++)
		{
			const float XOffset = (nr / nr_cuburi) * dist;
			const float YOffset = (nr % nr_cuburi) * dist;

			nr++;

			const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();

			AAvioaneBlock* NewBlock = GetWorld()->SpawnActor<AAvioaneBlock>(BlockLocation, FRotator(180.0f, 0, 0));
			NewBlock->SetActorScale3D({ scala_x,scala_y,scala_z });
			NewBlock->lin = i;
			NewBlock->coln = j;

			tabla[i][j] = NewBlock;

			if (NewBlock != nullptr)
			{
				NewBlock->acces = this;
			}
		}
	}
	for (TActorIterator<AAvion> it(GetWorld()); it; ++it)
	{
		if (it->ActorHasTag("Mare") && it->acces==this)
			avioane.Add(*it);
	}
	for (TActorIterator<AAvion> it(GetWorld()); it; ++it)
	{
		if (it->ActorHasTag("Mic") && it->acces==this)
			avioane.Add(*it);
	}
}

void AAvioaneBlockGrid::Evidentiere_Blocuri(int ok)
{
	for (int32 i = 0; i < nr_cuburi; i++)
	{
		for (int32 j = 0; j < nr_cuburi; j++)
		{
			if (tabla[i][j]->atins == true)
			{
				tabla[i][j]->Change_Mat(ok);
			}
		}
	}
}
#undef LOCTEXT_NAMESPACE