#include "Avion.h"
#include "AvioaneBlock.h"
#include "AvioanePawn.h"
#include "AvioaneBlockGrid.h"
#include "EngineUtils.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"
#include "Avion_Fals.h"


AAvion::AAvion()
{
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	mesh->OnClicked.AddDynamic(this, &AAvion::Click);

	val_rot = 0;
	nr = 0;

}

void AAvion::Click(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	//UE_LOG(LogTemp, Warning, TEXT("aproape aici?"));

	if (acces->este_avion_selectat == false)
	{
		selectat = true;
		acces->este_avion_selectat = true;

		//UE_LOG(LogTemp, Warning, TEXT("aici?"));
	}
	else if (acces->este_avion_selectat == true && selectat == true)
	{
		selectat = false;
		acces->este_avion_selectat = false;
	}
	else if (acces->este_avion_selectat == true && selectat == false)
	{
		for (int i=0;i<acces->avioane.Num();i++)
		{
			acces->avioane[i]->selectat = false;
		}	
		selectat = true;
	}
}

void AAvion::Setare_Material_PS(AAvioaneBlock * patrat, FString tip)
{
	if (tip == "Pilot")
	{
		patrat->BlockMesh->SetMaterial(0, patrat->Pilot_materiale[patrat->nr_culoare - 1]);
	}
	else
	{
		patrat->BlockMesh->SetMaterial(0, patrat->Motor_materiale[patrat->nr_culoare - 1]);
	}
}

void AAvion::Coordonate(AAvioaneBlock * patrat)
{
	
	int32 lin = patrat->lin;
	int32 coln = patrat->coln;
	int32 rotatie = ((int)val_rot / 90) % 4;

	if (patrat->tip == "Mic")
	{
		int dir_i[] = { 2,0,-2,0 }, dir_j[] = { 0,2,0,-2 };

		acces->tabla[lin + dir_i[rotatie]][coln + dir_j[rotatie]]->pilot = true;
		Setare_Material_PS(acces->tabla[lin + dir_i[rotatie]][coln + dir_j[rotatie]], "Pilot");
		
		dir_i[0] = 0, dir_i[1] = -1, dir_i[2] = 0, dir_i[3] = 1;
		dir_j[0] = 1, dir_j[1] = 0, dir_j[2] = -1, dir_j[3] = 0;
		
		acces->tabla[lin + dir_i[rotatie]][coln + dir_j[rotatie]]->motor = true;
		Setare_Material_PS(acces->tabla[lin + dir_i[rotatie]][coln + dir_j[rotatie]], "Motor");
		
		acces->tabla[lin - dir_i[rotatie]][coln - dir_j[rotatie]]->motor = true;
		Setare_Material_PS(acces->tabla[lin - dir_i[rotatie]][coln - dir_j[rotatie]], "Motor");

	}
	else
	{
		int dir_i[] = { 2,0,-2,0 }, dir_j[] = { 0,2,0,-2 }, dir_i2[] = { 0,0,-1,-1 }, dir_j2[] = { 0,1,1,0 };
		
		lin = lin + dir_i2[rotatie];
		coln = coln + dir_j2[rotatie];

		dir_i2[0] = 0, dir_i2[1] = -1, dir_i2[2] = 0, dir_i2[3] = 1;
		dir_j2[0] = 1, dir_j2[1] = 0, dir_j2[2] = -1, dir_j2[3] = 0;

		acces->tabla[lin + dir_i[rotatie]][coln + dir_j[rotatie]]->pilot = true;
		Setare_Material_PS(acces->tabla[lin + dir_i[rotatie]][coln + dir_j[rotatie]], "Pilot");

		acces->tabla[lin + dir_i2[rotatie] + dir_i[rotatie]][coln + dir_j2[rotatie] + dir_j[rotatie]]->pilot = true;
		Setare_Material_PS(acces->tabla[lin + dir_i2[rotatie] + dir_i[rotatie]][coln + dir_j2[rotatie] + dir_j[rotatie]], "Pilot");

		dir_i[0] = 0, dir_i[1] = -2, dir_i[2] = 0, dir_i[3] = 2;
		dir_j[0] = 2, dir_j[1] = 0, dir_j[2] = -2, dir_j[3] = 0;

		acces->tabla[lin + dir_i2[rotatie] + dir_i[rotatie]][coln + dir_j2[rotatie] + dir_j[rotatie]]->motor = true;
		Setare_Material_PS(acces->tabla[lin + dir_i2[rotatie] + dir_i[rotatie]][coln + dir_j2[rotatie] + dir_j[rotatie]], "Motor");

		acces->tabla[lin - dir_i[rotatie]][coln - dir_j[rotatie]]->motor = true;
		Setare_Material_PS(acces->tabla[lin - dir_i[rotatie]][coln - dir_j[rotatie]], "Motor");
	}
}
void AAvion::Rotire()
{
	if (selectat == true)
	{
		val_rot = val_rot + 90;
		this->SetActorRotation({ 0, val_rot, 0 });
		mesh_fals->SetActorRotation({ 0, val_rot, 0 });

		//UE_LOG(LogTemp, Warning, TEXT("sau aici?"));
	}
}

void AAvion::BeginPlay()
{
	Super::BeginPlay();

	tag = this->Tags[0];

	mesh->SetVisibility(false); // facem INVIZIBIL MESHUL
	mesh->OnComponentBeginOverlap.AddDynamic(this, &AAvion::OnOverlapBegin);
	mesh->OnComponentEndOverlap.AddDynamic(this, &AAvion::OnOverlapExit);

	locinit = GetActorLocation();

	
}

void AAvion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAvion::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		obiect_atins = Cast<AAvioaneBlock>(OtherActor);

		if (obiect_atins != nullptr)
		{
	
			if (obiect_atins->atins == false && obiect_atins->ocupat == false && this->selectat == true)
			{
				
				obiect_atins->atins = true;
				
				if (obiect_atins->siguranta == true)
				{
					nr++;
					if ((tag == "Mare" && nr == 24) || (tag == "Mic" && nr == 13))
					{
						acces->Evidentiere_Blocuri(true);
						acces->merge_pus = true;
					}
					else acces->Evidentiere_Blocuri(2);
				}
				else
				{
					acces->Evidentiere_Blocuri(2);
				}
			}
		}
	}
}

void AAvion::OnOverlapExit(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	obiect_atins = Cast<AAvioaneBlock>(OtherActor);

	if (obiect_atins != nullptr)
	{
		if (obiect_atins->ocupat == false)
		{
			acces->Evidentiere_Blocuri(false);
			obiect_atins->atins = false;
			nr--;
			if (obiect_atins->siguranta == false)
			{
				nr++;
			}
			acces->merge_pus = false;
		}
	}
}