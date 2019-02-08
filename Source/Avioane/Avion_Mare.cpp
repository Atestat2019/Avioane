// Fill out your copyright notice in the Description page of Project Settings.

#include "Avion_Mare.h"
#include "Avion_Mic.h"
#include "AvioaneBlock.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"
#include "AvioanePawn.h"
#include "EngineUtils.h"

// Sets default values
AAvion_Mare::AAvion_Mare()
{
	
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshhhh"));
	mesh->OnClicked.AddDynamic(this, &AAvion_Mare::Click_Mare);
	val_rot = 0;
}



void AAvion_Mare::Click_Mare(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	UE_LOG(LogTemp, Warning, TEXT("aproape aici?"));
	if (blabla->este_avion_selectat == false)
	{
		selectat_mare = true;
		blabla->este_avion_selectat = true;

		UE_LOG(LogTemp, Warning, TEXT("aici?"));
	}
	else if (blabla->este_avion_selectat == true && selectat_mare == true)
	{
		selectat_mare = false;
		blabla->este_avion_selectat = false;
	}
	else if (blabla->este_avion_selectat == true && selectat_mare == false)
	{
		selectat_mare = true;
		AAvion_Mic* test2;
		for (TActorIterator<AAvion_Mic> it(GetWorld()); it; ++it)
		{
			test2 = *it;

			if (test2->selectat_mic == true)
			{
				test2->selectat_mic = false;
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
		UE_LOG(LogTemp, Warning, TEXT("sau aici?"));
	}
}

// Called when the game starts or when spawned
void AAvion_Mare::BeginPlay()
{
	Super::BeginPlay();
	
	mesh->OnComponentBeginOverlap.AddDynamic(this, &AAvion_Mare::OnOverlapBegin);
	mesh->OnComponentEndOverlap.AddDynamic(this, &AAvion_Mare::OnOverlapExit);

	
	for (TActorIterator<AAvioanePawn> it(GetWorld()); it; ++it)
	{
		blabla = *it;
		break;
	}
}

// Called every frame
void AAvion_Mare::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAvion_Mare::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		obiect_atins = Cast<AAvioaneBlock>(OtherActor);

		if (obiect_atins != nullptr)
		{
			if (obiect_atins->atins == false)
			{
				obiect_atins->atins = true;
				UE_LOG(LogTemp, Warning, TEXT("A intrat in if"));
			}
		}
		
	}
}

void AAvion_Mare::OnOverlapExit(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("A iesit din if"));
}
