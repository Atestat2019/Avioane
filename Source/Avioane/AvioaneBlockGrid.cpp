#include "AvioaneBlockGrid.h"
#include "AvioaneBlock.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"
#include "Components/BoxComponent.h"
#include "EngineUtils.h"
#include "Avion_Mare.h"
#include "Avion_Mic.h"
#include "AvioanePawn.h"

#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"


AAvioaneBlockGrid::AAvioaneBlockGrid()
{
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	box = CreateDefaultSubobject<UBoxComponent>(TEXT("boxxxx"));
	
	box->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	box->OnBeginCursorOver.AddDynamic(this, &AAvioaneBlockGrid::OnCursorOver);
	box->OnEndCursorOver.AddDynamic(this, &AAvioaneBlockGrid::EndCursorOver);

	RootComponent = DummyRoot;

	Size = 20;
	BlockSpacing = 170.f;
	scala_x = scala_y = 0.6;
	scala_z = 0;
}


void AAvioaneBlockGrid::OnCursorOver(UPrimitiveComponent * Component)
{
	//UE_LOG(LogTemp, Warning, TEXT("aici?"));
	
	if (acces->avion_mare->selectat_mare == true)
	{
		acces->avion_mare->SetActorLocation(acces->avion_mare->locinit);
	}
	else
	{
		for (int i = 0; i < acces->avioane_mici.Num(); i++)
		{
			if (acces->avioane_mici[i]->selectat_mic == true)
			{
				if (acces->avioane_mici[i]->selectat_mic == true)
				{
					acces->avioane_mici[i]->SetActorLocation(acces->avioane_mici[i]->locinit);
				}
				break;
			}
		}
		
	}
}

void AAvioaneBlockGrid::EndCursorOver(UPrimitiveComponent * Component)
{
	//UE_LOG(LogTemp, Warning, TEXT("iese?"));
}


void AAvioaneBlockGrid::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<AAvioanePawn> it(GetWorld()); it; ++it)
	{
		acces = *it;
		break;
	}

	box->SetRelativeLocation({ 1620, 1620, -2 });
	box->SetWorldScale3D({ 10000, 10000, 0 });

	const int32 NumBlocks = Size * Size;
	int32 nr=0;

	for(int32 i=0; i<Size; i++)
	{
		for (int32 j = 0; j < Size; j++)
		{
			const float XOffset = (nr / Size) * BlockSpacing;
			const float YOffset = (nr%Size) * BlockSpacing;

			nr++;

			const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();

			AAvioaneBlock* NewBlock = GetWorld()->SpawnActor<AAvioaneBlock>(BlockLocation, FRotator(0, 0, 0));
			NewBlock->SetActorScale3D({ scala_x,scala_y,scala_z });
			
			tabla[i][j] = NewBlock;

			if (NewBlock != nullptr)
			{
				NewBlock->grida = this;
			}
		}
	}
}

void AAvioaneBlockGrid::Evidentiere_Blocuri(int ok)
{
	for (int32 i = 0; i < Size; i++)
	{
		for (int32 j = 0; j < Size; j++)
		{
			if (tabla[i][j]->atins == true)
			{
				tabla[i][j]->Change_Mat(ok);
			}
		}
	}
}



#undef LOCTEXT_NAMESPACE
