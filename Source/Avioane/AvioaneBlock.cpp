#include "AvioaneBlock.h"
#include "AvioaneBlockGrid.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"
#include "Avion_Mare.h"
#include "EngineUtils.h"
#include "Avion_Fals.h"
#include "Avion_Mic.h"

int AAvioaneBlock::k;
AAvioanePawn* AAvioaneBlock::acces;

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

	for (TActorIterator<AAvioanePawn> it(GetWorld()); it; ++it)
	{
		acces = *it;
		break;
	}
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

			for (i = 0; i < grida->Size; i++)
			{
				for (j = 0; j < grida->Size; j++)
				{
					patrat = grida->tabla[i][j];

					if (patrat->atins == true)
					{
						patrat->BlockMesh->SetMaterial(0, materiale[k]);
						patrat->ocupat = true;
						patrat->atins = false;
					}
				}
			}
			k++;

			//UE_LOG(LogTemp, Warning, TEXT("k are valoarea: %d"), k);	

			acces->este_avion_selectat = false;

			if (acces->avion_mare->selectat_mare == true)
			{
				acces->avion_mare->mesh->SetGenerateOverlapEvents(false);
				acces->avion_mare->mesh_fals->Destroy();
				acces->avion_mare->selectat_mare = false;
			}
			else
			{
				for (i = 0; i < acces->avioane_mici.Num(); i++)
				{
					if (acces->avioane_mici[i]->selectat_mic == true)
					{
						avion_mic = acces->avioane_mici[i];
						break;
					}
				}
				if (avion_mic->selectat_mic == true)
				{
					avion_mic->mesh->SetGenerateOverlapEvents(false);
					avion_mic->mesh_fals->Destroy();
					avion_mic->selectat_mic = false;
				}
			}

			//avion_mare->Destroy(); de studiat

			if (acces->contor_avioane == 4)
			{
				acces->intarziere();
			}
		}
	}
}

void AAvioaneBlock::Evidentiere(bool bOn)
{
	if (this->grida->ActorHasTag("Jucator"))
	{

		if (acces->avion_mare->selectat_mare == true)
		{
			if (bOn)
			{
				FVector loc = this->GetActorLocation();
				acces->avion_mare->SetActorLocation({ loc.X - 50 , loc.Y + 80 , 0 });
			}
		}
		else
		{
			int i;
			avion_mic = nullptr;

			for (i = 0; i < acces->avioane_mici.Num(); i++)
			{
				if (acces->avioane_mici[i]->selectat_mic == true)
				{
					avion_mic = acces->avioane_mici[i];
					break;
				}
			}
			if (avion_mic != nullptr && avion_mic->selectat_mic == true)
			{
				if (bOn)
				{
					FVector loc = this->GetActorLocation();
					avion_mic->SetActorLocation({ loc.X - 22, loc.Y , 0 });
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