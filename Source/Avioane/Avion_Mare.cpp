// Fill out your copyright notice in the Description page of Project Settings.

#include "Avion_Mare.h"
#include "AvioaneBlock.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"

// Sets default values
AAvion_Mare::AAvion_Mare()
{
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;
	// Set defaults
	Size = 3;
	BlockSpacing = 300.f;
	scala_x = scala_y = scala_z = 1;


}

	

	// Called when the game starts or when spawned
void AAvion_Mare::BeginPlay()
{
	Super::BeginPlay();

	// Number of blocks
	const int32 NumBlocks = Size * Size;

	int32 nr = 0;

	// Loop to spawn each block
	for (int32 i = 0; i < Size; i++)
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
				NewBlock->Grida_Avionului_Mare = this;
			}

		}
	}


	for (int32 j = 0; j < Size; j++)
	{
	
		for (int32 i = 0; i < Size; i++)
		{
			if ( i != 4 && (j==0 || j==7))
			{
				tabla[i][j]->Destroy();
			}
			if (i != 4 && i!=5 && (j == 1 || j == 6))
			{
				tabla[i][j]->Destroy();
			}
			if (i!=1 && i != 4 && i != 5 && (j == 2 || j == 5))
			{
				tabla[i][j]->Destroy();
			}
			if ((i == 0 || i == 7) && (j == 3 || j == 4))
			{
				tabla[i][j]->Destroy();
			}
		}

	}

	
}

// Called every frame
void AAvion_Mare::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

