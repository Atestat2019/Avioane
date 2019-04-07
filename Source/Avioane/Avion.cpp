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
				nr++;
				if ((tag=="Mare" && nr == 24) || (tag=="Mic" && nr==13))
				{
					acces->Evidentiere_Blocuri(true);
					acces->merge_pus = true;
				}
				else acces->Evidentiere_Blocuri(2);
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
			acces->merge_pus = false;
		}
	}
}