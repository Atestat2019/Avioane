#include "AvioaneBlockGrid.h"
#include "AvioaneBlock.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"

#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"


AAvioaneBlockGrid::AAvioaneBlockGrid()
{
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	Size = 20;
	BlockSpacing = 170.f;
	scala_x = scala_y = 0.6;
	scala_z = 0;
}

void AAvioaneBlockGrid::BeginPlay()
{
	Super::BeginPlay();

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

#undef LOCTEXT_NAMESPACE
