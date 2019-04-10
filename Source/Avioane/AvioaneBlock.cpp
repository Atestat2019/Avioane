#include "AvioaneBlock.h"
#include "AvioaneBlockGrid.h"
#include "AvioaneGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"
#include "Avion.h"
#include "EngineUtils.h"
#include "Avion_Fals.h"
#include "AvioanePawn.h"
#include "Engine/Classes/GameFramework/Controller.h"
#include "Engine/Classes/GameFramework/PlayerController.h"
 

int AAvioaneBlock::k;

AAvioaneBlock::AAvioaneBlock()
{
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
		{}
	};

	static FConstructorStatics ConstructorStatics;

	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(1.f, 1.f, 0.25f));
	BlockMesh->SetRelativeLocation(FVector(0.f, 0.f, 25.f));
	BlockMesh->SetMaterial(0, ConstructorStatics.BlueMaterial.Get());
	BlockMesh->SetupAttachment(DummyRoot);
	BlockMesh->OnClicked.AddDynamic(this, &AAvioaneBlock::HandleClicked);

	BaseMaterial = ConstructorStatics.BaseMaterial.Get();
	BlueMaterial = ConstructorStatics.BlueMaterial.Get();
	OrangeMaterial = ConstructorStatics.OrangeMaterial.Get();

	materiale.Add(ConstructorStatics.Material_Rosu.Get());

	materiale.Add(ConstructorStatics.Material_Albastru.Get());
	materiale.Add(ConstructorStatics.Material_Verde.Get());
	materiale.Add(ConstructorStatics.Material_Galben.Get());

	atins = false;
	ocupat = false;

	k = 0;
}

void AAvioaneBlock::BeginPlay()
{
	Super::BeginPlay();
}

void AAvioaneBlock::HandleClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	int i, j;

	if (acces->este_avion_selectat == true)
	{
		if (acces->merge_pus == true)
		{
			AAvioaneBlock* patrat;

			acces->contor_avioane++;

			for (i = 0; i < acces->Size; i++)
			{
				for (j = 0; j < acces->Size; j++)
				{
					patrat = acces->tabla[i][j];

					if (patrat->atins == true)
					{
						patrat->BlockMesh->SetMaterial(0, materiale[k%4]);
						patrat->ocupat = true;
						patrat->atins = false;
					}
				}
			}
			k++;

			//UE_LOG(LogTemp, Warning, TEXT("k are valoarea: %d"), k);	

			acces->este_avion_selectat = false;

			for (int i = 0; i < acces->avioane.Num(); i++)
			{
				if (acces->avioane[i]->selectat == true)
				{
					acces->avioane[i]->mesh->SetGenerateOverlapEvents(false);
					acces->avioane[i]->mesh_fals->Destroy();
					acces->avioane[i]->selectat = false;
				}
			}
			//avioane[i]->Destroy(); de studiat

			if (acces->ActorHasTag("Jucator") && acces->contor_avioane == 4)
			{
				//acces->intarziere();
				//AAvioaneGameMode* GameMode = (AAvioaneGameMode*)(GetWorld()->GetAuthGameMode());
				//GameMode->Pawn->intarziere();

				AAvioaneGameMode* GM = GetWorld()->GetAuthGameMode<AAvioaneGameMode>();
				GM->Jucatori[0]->intarziere();
				
			}
		}
	}
}

void AAvioaneBlock::Evidentiere(bool bOn)
{
		for (int i = 0; i < acces->avioane.Num(); i++)
		{
			if (acces->avioane[i]->selectat == true)
			{
				if (bOn)
				{
					FVector loc = this->GetActorLocation();
					
					if (acces->avioane[i]->ActorHasTag("Mare"))
					{
						acces->avioane[i]->SetActorLocation({ loc.X - 50 , loc.Y + 80 , 0 });
					}
					else
					{
						acces->avioane[i]->SetActorLocation({ loc.X - 22, loc.Y , 0 });
					}
				}
			}
		}
}

void AAvioaneBlock::Change_Mat(int bOn)
{
	if (bOn==1)
	{
		BlockMesh->SetMaterial(0, BaseMaterial);
	}
	else if (bOn==0)
	{
		BlockMesh->SetMaterial(0, BlueMaterial);
	}
	else
	{
		BlockMesh->SetMaterial(0, materiale[0]);
	}
}