#include "Avion_Mare.h"
#include "Avion_Mic.h"
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


AAvion_Mare::AAvion_Mare()
{
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	mesh->OnClicked.AddDynamic(this, &AAvion_Mare::Click_Mare);

	val_rot = 0;
	nr = 0;
}

void AAvion_Mare::Click_Mare(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	//UE_LOG(LogTemp, Warning, TEXT("aproape aici?"));

	if (acces->este_avion_selectat == false)
	{
		selectat_mare = true;
		acces->este_avion_selectat = true;

		//UE_LOG(LogTemp, Warning, TEXT("aici?"));
	}
	else if (acces->este_avion_selectat == true && selectat_mare == true)
	{
		selectat_mare = false;
		acces->este_avion_selectat = false;
	}
	else if (acces->este_avion_selectat == true && selectat_mare == false)
	{
		selectat_mare = true;
		AAvion_Mic* cautare3 = nullptr;;

		for (TActorIterator<AAvion_Mic> it(GetWorld()); it; ++it)
		{
			if (it->tabla->ActorHasTag("Jucator"))
				cautare3 = *it;

			if (cautare3 != nullptr)
			{
				if (cautare3->selectat_mic == true)
				{
					cautare3->selectat_mic = false;
				}
			}
		}
	}
}

void AAvion_Mare::Rotire_Mare()
{
	if (selectat_mare == true)
	{
		val_rot = val_rot + 90;
		this->SetActorRotation({ 0, val_rot, 0 });
		mesh_fals->SetActorRotation({ 0, val_rot, 0 });

		//UE_LOG(LogTemp, Warning, TEXT("sau aici?"));
	}
}

void AAvion_Mare::BeginPlay()
{
	Super::BeginPlay();

	mesh->SetVisibility(false); // facem INVIZIBIL MESHUL
	mesh->OnComponentBeginOverlap.AddDynamic(this, &AAvion_Mare::OnOverlapBegin);
	mesh->OnComponentEndOverlap.AddDynamic(this, &AAvion_Mare::OnOverlapExit);

	locinit = GetActorLocation();


	for (TActorIterator<AAvioanePawn> it(GetWorld()); it; ++it)
	{
		acces = *it;
		break;
	}

}

void AAvion_Mare::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AAvion_Mare::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		obiect_atins = Cast<AAvioaneBlock>(OtherActor);
		//tabla_atinsa = Cast<AAvioaneBlockGrid>(OtherActor);

		if (obiect_atins != nullptr)
		{
			//mesh->bVisible = false;

			if (obiect_atins->atins == false && obiect_atins->ocupat==false && this->selectat_mare==true)
			{
				obiect_atins->atins = true;
				nr++;
				if (nr == 24)
				{
					//UE_LOG(LogTemp, Warning, TEXT("A intrat bine"));
					tabla->Evidentiere_Blocuri(true);
					acces->merge_pus = true;
				}
				else tabla->Evidentiere_Blocuri(2);
				//obiect_atins->Change_Mat(true);

				//UE_LOG(LogTemp, Warning, TEXT("A intrat avion_mare mare"));
			}
		}
		/*
		if (tabla_atinsa != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("A intrat avion mare in tabla"));
		}
		*/
	}
}

void AAvion_Mare::OnOverlapExit(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//UE_LOG(LogTemp, Warning, TEXT("A iesit din if"));

	obiect_atins = Cast<AAvioaneBlock>(OtherActor);

	if (obiect_atins != nullptr)
	{
		//if (obiect_atins->atins == true)

		if (obiect_atins->ocupat==false)
		{
			tabla->Evidentiere_Blocuri(false);
			obiect_atins->atins = false;
			nr--;
			acces->merge_pus = false;

			//obiect_atins->Change_Mat(false);

			//UE_LOG(LogTemp, Warning, TEXT("A iesit avion_mare mare"));
		}
	}
	/*
	if (tabla_atinsa != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("A iesit avion mare din tabla"));
	}
	*/
}
