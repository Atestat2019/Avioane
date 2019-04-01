#include "Avion_Mic.h"
#include "AvioanePawn.h"
#include "Avion_Mare.h"
#include "AvioaneBlock.h"
#include "EngineUtils.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "Avion_Fals.h"
#include "AvioaneBlockGrid.h"


AAvion_Mic::AAvion_Mic()
{
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshhhh"));
	mesh->OnClicked.AddDynamic(this, &AAvion_Mic::Click_Mic);

	val_rot = 0;
}

void AAvion_Mic::Click_Mic(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	//UE_LOG(LogTemp, Warning, TEXT("aproape mic aici?"));

	if (acces->este_avion_selectat == false)
	{
		selectat_mic = true;
		acces->este_avion_selectat = true;

		//UE_LOG(LogTemp, Warning, TEXT("mic aici?"));
	}
	else if (acces->este_avion_selectat == true && selectat_mic == true)
	{
		selectat_mic = false;
		acces->este_avion_selectat = false;
	}
	else if (acces->este_avion_selectat == true && selectat_mic == false)
	{
		selectat_mic = true;
		AAvion_Mic* cautare1=nullptr;

		for (TActorIterator<AAvion_Mic> it(GetWorld()); it; ++it)
		{
			if (it->tabla->ActorHasTag("Jucator"))
				cautare1 = *it;

			if (cautare1 != this && cautare1->selectat_mic==true)
			{
				cautare1->selectat_mic = false;
			}
		}
		AAvion_Mare* cautare2=nullptr;

		for (TActorIterator<AAvion_Mare> it(GetWorld()); it; ++it)
		{
			if (it->tabla->ActorHasTag("Jucator"))
				cautare2 = *it;

			if (cautare2 != nullptr)
			{
				if(cautare2->selectat_mare == true)
				{
					cautare2->selectat_mare = false;
				}
			}
		}
	}
}

void AAvion_Mic::Rotire_Mic()
{
	if (selectat_mic == true)
	{
		val_rot = val_rot + 90;
		this->SetActorRotation({ 0, val_rot, 0 });
		mesh_fals->SetActorRotation({ 0, val_rot, 0 });

		//UE_LOG(LogTemp, Warning, TEXT("sau mic aici?"));
	}
}

void AAvion_Mic::BeginPlay()
{
	Super::BeginPlay();

	locinit = GetActorLocation();
	
	mesh->SetVisibility(false);
	mesh->OnComponentBeginOverlap.AddDynamic(this, &AAvion_Mic::OnOverlapBegin);
	mesh->OnComponentEndOverlap.AddDynamic(this, &AAvion_Mic::OnOverlapExit);

	for (TActorIterator<AAvioanePawn> it(GetWorld()); it; ++it)
	{
		acces = *it;
		break;
	}

}

void AAvion_Mic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAvion_Mic::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		obiect_atins = Cast<AAvioaneBlock>(OtherActor);

		if (obiect_atins != nullptr)
		{
			if (obiect_atins->atins == false && obiect_atins->ocupat == false && this->selectat_mic==true)
			{
				obiect_atins->atins = true;

				nr++;
				if (nr == 13)
				{
					//UE_LOG(LogTemp, Warning, TEXT("A intrat bine"));
					tabla->Evidentiere_Blocuri(true);
					acces->merge_pus = true;
				}
				else tabla->Evidentiere_Blocuri(2);
				
				
				//obiect_atins->Change_Mat(true);
				
				//UE_LOG(LogTemp, Warning, TEXT("A intrat avion_mare mic"));
			}
		}
	}
}

void AAvion_Mic::OnOverlapExit(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	obiect_atins = Cast<AAvioaneBlock>(OtherActor);

	if (obiect_atins != nullptr)
	{
		if (obiect_atins->ocupat == false)
		{
			tabla->Evidentiere_Blocuri(false);
			obiect_atins->atins = false;
			nr--;
			acces->merge_pus = false;
			//obiect_atins->Change_Mat(false);

			//UE_LOG(LogTemp, Warning, TEXT("A iesit avion_mare mare"));
		}
	}
}
