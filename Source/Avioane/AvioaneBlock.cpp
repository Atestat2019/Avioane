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
 

int32 AAvioaneBlock::nr_mat;
AAvioaneGameMode* AAvioaneBlock::GM;
TArray<UMaterialInstance*> AAvioaneBlock::materiale;
TArray<UMaterial*> AAvioaneBlock::X_materiale;
bool AAvioaneBlock::ok=true;

AAvioaneBlock::AAvioaneBlock()
{
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Material_Gri;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Material_0;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Material_Rosu;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Material_Albastru;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Material_Celest;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Material_Coada_de_Vaca;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Material_Mar;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Material_Mov;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Material_Nectar;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Material_Negru;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Material_Portocaliu;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Material_Verde;

		ConstructorHelpers::FObjectFinderOptional<UMaterial> XGriMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> XAlbastruMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> XCelestMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> XCoada_de_VacaMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> XMarMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> XMovMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> XNectarMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> XNegruMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> XPortocaliuMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> XVerdeMaterial;

		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Puzzle/StaticMeshes/PuzzleCube.PuzzleCube"))
			, BaseMaterial(TEXT("/Game/Puzzle/Meshes/BaseMaterial.BaseMaterial"))
			, Material_Gri(TEXT("/Game/Puzzle/Meshes/Material_Gri.Material_Gri"))
			, Material_0(TEXT("/Game/Puzzle/Meshes/Material_0.Material_0"))
			, Material_Rosu(TEXT("/Game/Puzzle/Meshes/Material_Rosu.Material_Rosu"))
			, Material_Albastru(TEXT("/Game/Puzzle/Meshes/Material_Albastru.Material_Albastru"))
			, Material_Celest(TEXT("/Game/Puzzle/Meshes/Material_Celest.Material_Celest"))
			, Material_Negru(TEXT("/Game/Puzzle/Meshes/Material_Negru.Material_Negru"))
			, Material_Coada_de_Vaca(TEXT("/Game/Puzzle/Meshes/Material_Coada_de_Vaca.Material_Coada_de_Vaca"))
			, Material_Mar(TEXT("/Game/Puzzle/Meshes/Material_Mar.Material_Mar"))
			, Material_Mov(TEXT("/Game/Puzzle/Meshes/Material_Mov.Material_Mov"))
			, Material_Nectar(TEXT("/Game/Puzzle/Meshes/Material_Nectar.Material_Nectar"))
			, Material_Portocaliu(TEXT("/Game/Puzzle/Meshes/Material_Portocaliu.Material_Portocaliu"))
			, Material_Verde(TEXT("/Game/Puzzle/Meshes/Material_Verde.Material_Verde"))

			, XGriMaterial(TEXT("/Game/Puzzle/Meshes/XGriMaterial.XGriMaterial"))
			, XAlbastruMaterial(TEXT("/Game/Puzzle/Meshes/XAlbastruMaterial.XAlbastruMaterial"))
			, XCelestMaterial(TEXT("/Game/Puzzle/Meshes/XCelestMaterial.XCelestMaterial"))
			, XNegruMaterial(TEXT("/Game/Puzzle/Meshes/XNegruMaterial.XNegruMaterial"))
			, XCoada_de_VacaMaterial(TEXT("/Game/Puzzle/Meshes/XCoada_de_VacaMaterial.XCoada_de_VacaMaterial"))
			, XMarMaterial(TEXT("/Game/Puzzle/Meshes/XMarMaterial.XMarMaterial"))
			, XMovMaterial(TEXT("/Game/Puzzle/Meshes/XMovMaterial.XMovMaterial"))
			, XNectarMaterial(TEXT("/Game/Puzzle/Meshes/XNectarMaterial.XNectarMaterial"))
			, XPortocaliuMaterial(TEXT("/Game/Puzzle/Meshes/XPortocaliuMaterial.XPortocaliuMaterial"))
			, XVerdeMaterial(TEXT("/Game/Puzzle/Meshes/XVerdeMaterial.XVerdeMaterial"))
		{}
	}; 

	static FConstructorStatics ConstructorStatics;

	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(1.f, 1.f, 0.25f));
	BlockMesh->SetRelativeLocation(FVector(0.f, 0.f, 25.f));
	BlockMesh->SetMaterial(0, ConstructorStatics.Material_Gri.Get());
	BlockMesh->SetupAttachment(DummyRoot);
	BlockMesh->OnClicked.AddDynamic(this, &AAvioaneBlock::HandleClicked);

	BaseMaterial = ConstructorStatics.BaseMaterial.Get();
	Material_Gri = ConstructorStatics.Material_Gri.Get();
	Material_0 = ConstructorStatics.Material_0.Get();
	XGriMaterial = ConstructorStatics.XGriMaterial.Get();

	if (ok == true)
	{
		materiale.Add(ConstructorStatics.Material_Rosu.Get());
		materiale.Add(ConstructorStatics.Material_Albastru.Get());
		materiale.Add(ConstructorStatics.Material_Celest.Get());
		materiale.Add(ConstructorStatics.Material_Coada_de_Vaca.Get());
		materiale.Add(ConstructorStatics.Material_Mar.Get());
		materiale.Add(ConstructorStatics.Material_Mov.Get());
		materiale.Add(ConstructorStatics.Material_Nectar.Get());
		materiale.Add(ConstructorStatics.Material_Negru.Get());
		materiale.Add(ConstructorStatics.Material_Portocaliu.Get());
		materiale.Add(ConstructorStatics.Material_Verde.Get());

		X_materiale.Add(ConstructorStatics.XAlbastruMaterial.Get());
		X_materiale.Add(ConstructorStatics.XCelestMaterial.Get());
		X_materiale.Add(ConstructorStatics.XCoada_de_VacaMaterial.Get());
		X_materiale.Add(ConstructorStatics.XMarMaterial.Get());
		X_materiale.Add(ConstructorStatics.XMovMaterial.Get());
		X_materiale.Add(ConstructorStatics.XNectarMaterial.Get());
		X_materiale.Add(ConstructorStatics.XNegruMaterial.Get());
		X_materiale.Add(ConstructorStatics.XPortocaliuMaterial.Get());
		X_materiale.Add(ConstructorStatics.XVerdeMaterial.Get());

		ok = false;
	}
	
	atins = false;
	ocupat = false;
	pilot = false;
	motor = false;
	siguranta = true;
	nr_culoare = -1;
}

void AAvioaneBlock::Bordare(AAvioaneBlock* patrat)
{
	int32 x = patrat->lin, y = patrat->coln;

	int dir_i[] = { 1,0,-1,0 }, dir_j[] = { 0,1,0,-1 };

	for (int32 directie = 0; directie < 4; directie++)
	{
		x = patrat->lin + dir_i[directie];
		y = patrat->coln + dir_j[directie];

		if (x < 20 && x>=0 && y < 20 && y>=0)
		{
			UE_LOG(LogTemp, Warning, TEXT("x este : %d, y este : %d"), x, y);
			//acces->tabla[x][y]->ocupat = true;
			acces->tabla[x][y]->siguranta = false;
		}
	}
}

void AAvioaneBlock::BeginPlay()
{
	Super::BeginPlay();

	GM = GetWorld()->GetAuthGameMode<AAvioaneGameMode>();


}



void AAvioaneBlock::HandleClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	int i, j;

	if (GM->Stadiu == 2)
	{
		GM->Lovitura(this);
	}
	else
	{
		if (acces->este_avion_selectat == true)
		{
			if (acces->merge_pus == true)
			{
				AAvion* avion = nullptr;

				for (int i = 0; i < acces->avioane.Num(); i++)
				{
					if (acces->avioane[i]->selectat == true)
					{
						avion = acces->avioane[i];
					}
				}
				AAvioaneBlock* patrat;
				acces->contor_avioane++;
				nr_mat = FMath::RandRange(1, materiale.Num() - 1);

				while (acces->frecv[nr_mat] != 0)
				{
					nr_mat = FMath::RandRange(1, materiale.Num() - 1);
				}
				acces->frecv[nr_mat] = 1;

				for (i = 0; i < acces->Size; i++)
				{
					for (j = 0; j < acces->Size; j++)
					{
						patrat = acces->tabla[i][j];

						if (patrat->atins == true)
						{
							patrat->BlockMesh->SetMaterial(0, materiale[nr_mat]);
							patrat->nr_culoare = nr_mat;
							Bordare(patrat);
							patrat->ocupat = true;
							patrat->atins = false;
							if (acces->avioane[0]->selectat == true)
								patrat->tip = "Mare";
							else
								patrat->tip = "Mic";
						}
					}
				}
				acces->este_avion_selectat = false;
				avion->Coordonate(this);
				avion->mesh->SetGenerateOverlapEvents(false);
				avion->mesh_fals->Destroy();
				avion->selectat = false;

				//avioane[i]->Destroy(); de studiat

				if (acces->ActorHasTag("Jucator") && acces->contor_avioane == 4)
				{
					GM->Colorare_Tabla(0);
					GM->Jucatori[0]->intarziere();
					GM->Stadiu = 2;
					GM->Jucatori[0]->Tura();
				}
			}
		}
	}
}

void AAvioaneBlock::Evidentiere(bool bOn)
{
	if (GM->Safe(this))
	{
		Change_Mat(bOn);
	}
	else
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
}

void AAvioaneBlock::Change_Mat(int bOn)
{
	if (bOn==1)
	{
		BlockMesh->SetMaterial(0, BaseMaterial);
	}
	else if (bOn==0)
	{
		BlockMesh->SetMaterial(0, Material_Gri);
	}
	else
	{
		BlockMesh->SetMaterial(0, materiale[0]);
	}
}