// Fill out your copyright notice in the Description page of Project Settings.

#include "Avion_Mic.h"
#include "Avion_Mare.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"
#include "EngineUtils.h"
#include "AvioanePawn.h"

// Sets default values
AAvion_Mic::AAvion_Mic()
{
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshhhh"));
	mesh->OnClicked.AddDynamic(this, &AAvion_Mic::Click_Mic);

	val_rot = 0;
}

void AAvion_Mic::Click_Mic(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	UE_LOG(LogTemp, Warning, TEXT("aproape mic aici?"));
	if (blabla->este_avion_selectat == false)
	{
		selectat_mic = true;
		blabla->este_avion_selectat = true;

		UE_LOG(LogTemp, Warning, TEXT("mic aici?"));
	}
	else if (blabla->este_avion_selectat == true && selectat_mic == true)
	{
		selectat_mic = false;
		blabla->este_avion_selectat = false;
	}
	else if (blabla->este_avion_selectat == true && selectat_mic == false)
	{
		selectat_mic = true;
		AAvion_Mic* test;
		for (TActorIterator<AAvion_Mic> it(GetWorld()); it; ++it)
		{
			test = *it;

			if (test != this && test->selectat_mic==true)
			{
				test->selectat_mic = false;
			}
		}

		AAvion_Mare* test3;
		for (TActorIterator<AAvion_Mare> it(GetWorld()); it; ++it)
		{
			test3 = *it;

			if (test3->selectat_mare == true)
			{
				test3->selectat_mare = false;
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
		UE_LOG(LogTemp, Warning, TEXT("sau mic aici?"));
	}
}

	// Called when the game starts or when spawned
void AAvion_Mic::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<AAvioanePawn> it(GetWorld()); it; ++it)
	{
		blabla = *it;
		break;
	}
}

// Called every frame
void AAvion_Mic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
