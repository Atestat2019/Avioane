// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "AvioaneBlockGrid.h"
#include "AvioaneBlock.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"

#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"

AAvioaneBlockGrid::AAvioaneBlockGrid()
{
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	ScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText0"));
	ScoreText->SetRelativeLocation(FVector(200.f,0.f,0.f));
	ScoreText->SetRelativeRotation(FRotator(90.f,0.f,0.f));
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Score: {0}"), FText::AsNumber(0)));
	ScoreText->SetupAttachment(DummyRoot);

	// Set defaults
	Size = 3;
	BlockSpacing = 300.f;
	scala_x = scala_y = scala_z = 1;
}


void AAvioaneBlockGrid::BeginPlay()
{
	Super::BeginPlay();

	// Number of blocks
	const int32 NumBlocks = Size * Size;

	int32 nr=0;

	// Loop to spawn each block
	for(int32 i=0; i<Size; i++)
	{
		
		
		for (int32 j = 0; j < Size; j++)
		{
			
			
			const float XOffset = (nr / Size) * BlockSpacing; // Divide by dimension
			const float YOffset = (nr%Size) * BlockSpacing; // Modulo gives remainder

			nr++;

			// Make position vector, offset from Grid location
			const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();

			// Spawn a block
			AAvioaneBlock* NewBlock = GetWorld()->SpawnActor<AAvioaneBlock>(BlockLocation, FRotator(0, 0, 0));
			NewBlock->SetActorScale3D({ scala_x,scala_y,scala_z });
			
			
			tabla[i][j] = NewBlock;


			// Tell the block about its owner
			if (NewBlock != nullptr)
			{
				NewBlock->OwningGrid = this;
			}

		}
		
	}

}


void AAvioaneBlockGrid::AddScore()
{
	// Increment score
	Score++;

	// Update text
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Score: {0}"), FText::AsNumber(Score)));
}

#undef LOCTEXT_NAMESPACE
