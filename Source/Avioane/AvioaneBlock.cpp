// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "AvioaneBlock.h"
#include "AvioaneBlockGrid.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"
#include "Avion_Mare.h"
#include "EngineUtils.h"
#include "MyActor3.h"
#include "Avion_Mic.h"

int AAvioaneBlock::i;

AAvioaneBlock::AAvioaneBlock()
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BlueMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> OrangeMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Material_Rosu;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Material_Albastru;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Material_Verde;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Material_Galben;

		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Puzzle/Meshes/PuzzleCube.PuzzleCube"))
			, BaseMaterial(TEXT("/Game/Puzzle/Meshes/BaseMaterial.BaseMaterial"))
			, BlueMaterial(TEXT("/Game/Puzzle/Meshes/BlueMaterial.BlueMaterial"))
			, OrangeMaterial(TEXT("/Game/Puzzle/Meshes/OrangeMaterial.OrangeMaterial"))
			, Material_Rosu(TEXT("/Game/Puzzle/Meshes/Material_Rosu.Material_Rosu"))
			, Material_Albastru(TEXT("/Game/Puzzle/Meshes/Material_Albastru.Material_Albastru"))
			, Material_Verde(TEXT("/Game/Puzzle/Meshes/Material_Verde.Material_Verde"))
			, Material_Galben(TEXT("/Game/Puzzle/Meshes/Material_Galben.Material_Galben"))
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

	BaseMaterial = ConstructorStatics.BaseMaterial.Get();
	BlueMaterial = ConstructorStatics.BlueMaterial.Get();
	OrangeMaterial = ConstructorStatics.OrangeMaterial.Get();

	materiale.Add(ConstructorStatics.Material_Rosu.Get());
	materiale.Add(ConstructorStatics.Material_Albastru.Get());
	materiale.Add(ConstructorStatics.Material_Verde.Get());
	materiale.Add(ConstructorStatics.Material_Galben.Get());

	atins = false;
	ocupat = false;
	i = 0;
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
		avion_mare = *it;
		break;
	}

	if (avion_mare->selectat_mare == true)
	{
		for (TActorIterator<AAvioaneBlock> it(GetWorld()); it; ++it)
		{
			test = *it;
			if (test->atins == true)
			{
				test->BlockMesh->SetMaterial(0, materiale[i]);
				test->ocupat = true;
				test->atins = false;
			}
		}
		i++;
		//UE_LOG(LogTemp, Warning, TEXT("i are valoarea: %d"), i);
		avion_mare->mesh->SetGenerateOverlapEvents(false);
		avion_mare->mesh_fals->Destroy();
		avion_mare->selectat_mare = false;
	}
	else
	{
		for (TActorIterator<AAvion_Mic> it(GetWorld()); it; ++it)
		{
			avion_mic = *it;
			
			if (avion_mic->selectat_mic == true) 
			{
				break;
			}
		}
		if (avion_mic->selectat_mic == true)
		{
			for (TActorIterator<AAvioaneBlock> it(GetWorld()); it; ++it)
			{
				test = *it;
				if (test->atins == true)
				{
					test->BlockMesh->SetMaterial(0, materiale[i]);
					test->ocupat = true;
					test->atins = false;
				}
			}
			i++;
			//UE_LOG(LogTemp , Warning, TEXT("i are valoarea: %d"), i);
			avion_mic->mesh->SetGenerateOverlapEvents(false);
			avion_mic->mesh_fals->Destroy();
			avion_mic->selectat_mic = false;
		}

	}
	
	//avion_mare->Destroy(); de studiat


	// Check we are not already active
	/*
	if (!bIsActive)
	{
		bIsActive = true;

		// Change material
		BlockMesh->SetMaterial(0, OrangeMaterial);


		// Tell the Grid
		if (OwningGrid != nullptr)
		{
			OwningGrid->AddScore();
		}
	}
	*/
}

void AAvioaneBlock::Highlight(bool bOn)
{
	// Do not highlight if the block has already been activated.

	if (bIsActive)
	{
		return;
	}



	for (TActorIterator<AAvion_Mare> it(GetWorld()); it; ++it)
	{
		avion_mare = *it;
		break;
	}
	
	if (avion_mare->selectat_mare == true)
	{

		if (bOn)
		{

			FVector loc = this->GetActorLocation();
			avion_mare->SetActorLocation({ loc.X - 50 , loc.Y + 80 , 0 });
			
		}

	}
	else
	{
		for (TActorIterator<AAvion_Mic> it(GetWorld()); it; ++it)
		{
			avion_mic = *it;
			if (avion_mic->selectat_mic == true)
			{
				break;
			}
		}
		if (avion_mic->selectat_mic == true)
		{

			if (bOn)
			{

				FVector loc = this->GetActorLocation();

				avion_mic->SetActorLocation({ loc.X - 22, loc.Y , 0 });

			}
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
