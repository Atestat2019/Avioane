#include "Avion_Mic.h"
#include "AvioanePawn.h"
#include "Avion_Mare.h"
#include "EngineUtils.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstance.h"
#include "UObject/ConstructorHelpers.h"


AAvion_Mic::AAvion_Mic()
{
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshhhh"));
	mesh->OnClicked.AddDynamic(this, &AAvion_Mic::Click_Mic);

	val_rot = 0;
}

void AAvion_Mic::Click_Mic(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	//UE_LOG(LogTemp, Warning, TEXT("aproape mic aici?"));

	if (acces_selectat->este_avion_selectat == false)
	{
		selectat_mic = true;
		acces_selectat->este_avion_selectat = true;

		//UE_LOG(LogTemp, Warning, TEXT("mic aici?"));
	}
	else if (acces_selectat->este_avion_selectat == true && selectat_mic == true)
	{
		selectat_mic = false;
		acces_selectat->este_avion_selectat = false;
	}
	else if (acces_selectat->este_avion_selectat == true && selectat_mic == false)
	{
		selectat_mic = true;
		AAvion_Mic* cautare1;

		for (TActorIterator<AAvion_Mic> it(GetWorld()); it; ++it)
		{
			cautare1 = *it;

			if (cautare1 != this && cautare1->selectat_mic==true)
			{
				cautare1->selectat_mic = false;
			}
		}
		AAvion_Mare* cautare2;

		for (TActorIterator<AAvion_Mare> it(GetWorld()); it; ++it)
		{
			cautare2 = *it;

			if (cautare2->selectat_mare == true)
			{
				cautare2->selectat_mare = false;
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
		
		//UE_LOG(LogTemp, Warning, TEXT("sau mic aici?"));
	}
}

void AAvion_Mic::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<AAvioanePawn> it(GetWorld()); it; ++it)
	{
		acces_selectat = *it;
		break;
	}
}

void AAvion_Mic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
