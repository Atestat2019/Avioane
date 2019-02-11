// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "AvioaneBlock.h"
#include "AvioaneBlockGrid.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"
#include "Avion_Mare.h"
#include "EngineUtils.h"

AAvioaneBlock::AAvioaneBlock()
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BlueMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> OrangeMaterial;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Puzzle/Meshes/PuzzleCube.PuzzleCube"))
			, BaseMaterial(TEXT("/Game/Puzzle/Meshes/BaseMaterial.BaseMaterial"))
			, BlueMaterial(TEXT("/Game/Puzzle/Meshes/BlueMaterial.BlueMaterial"))
			, OrangeMaterial(TEXT("/Game/Puzzle/Meshes/OrangeMaterial.OrangeMaterial"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(1.f,1.f,0.25f));
	BlockMesh->SetRelativeLocation(FVector(0.f,0.f,25.f));
	BlockMesh->SetMaterial(0, ConstructorStatics.BlueMaterial.Get());
	BlockMesh->SetupAttachment(DummyRoot);
	BlockMesh->OnClicked.AddDynamic(this, &AAvioaneBlock::BlockClicked);
	BlockMesh->OnInputTouchBegin.AddDynamic(this, &AAvioaneBlock::OnFingerPressedBlock);

	// Save a pointer to the orange material
	BaseMaterial = ConstructorStatics.BaseMaterial.Get();
	BlueMaterial = ConstructorStatics.BlueMaterial.Get();
	OrangeMaterial = ConstructorStatics.OrangeMaterial.Get();

	/*
	FVector scala;
	scala.X = 1;
	scala.Y = 1;
	scala.Z = 0.001;
	this->SetActorScale3D(scala);
	*/

	//this->SetActorScale3D({ 0.5, 0.5, 0 });

	atins = false;
	clicked = false;
}

void AAvioaneBlock::BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	HandleClicked();
}


void AAvioaneBlock::OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	HandleClicked();
}

void AAvioaneBlock::HandleClicked()
{
	
	//trebuie schimbata - e ineficienta
	
	AAvioaneBlock* test;
	
	for (TActorIterator<AAvion_Mare> it(GetWorld()); it; ++it)
	{
		avion = *it;
		break;
	}
	for (TActorIterator<AAvioaneBlock> it(GetWorld()); it; ++it)
	{
		
		
		
		
		test = *it;
		if (test->atins == true)
		{
			test->BlockMesh->SetMaterial(0, OrangeMaterial);
			test->clicked = true;
		}


	}
	

	// Check we are not already active
	if (!bIsActive)
	{
		bIsActive = true;

		// Change material
		BlockMesh->SetMaterial(0, OrangeMaterial);

		avion->go = true;

		// Tell the Grid
		if (OwningGrid != nullptr)
		{
			OwningGrid->AddScore();
		}
	}
}

void AAvioaneBlock::Highlight(bool bOn)
{
	// Do not highlight if the block has already been activated.
	
	for (TActorIterator<AAvion_Mare> it(GetWorld()); it; ++it)
	{
		avion = *it;
		break;
	}

	if (bIsActive)
	{
		return;
	}
	if (bOn)
	{

		FVector loc = this->GetActorLocation();
		
		if (avion->selectat_mare == true)
		{
			avion->SetActorLocation({ loc.X - 50, loc.Y + 80, 0 });
		}
	}

}

void AAvioaneBlock::Change_Mat(bool bOn)
{
	if (bOn)
	{
		BlockMesh->SetMaterial(0, BaseMaterial);

	}
	else
	{
		BlockMesh->SetMaterial(0, BlueMaterial);
	}
}
