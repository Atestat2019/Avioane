// Fill out your copyright notice in the Description page of Project Settings.

#include "Avion_Mic.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"

// Sets default values
AAvion_Mic::AAvion_Mic()
{
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshhhh"));
	mesh->OnClicked.AddDynamic(this, &AAvion_Mic::Rotire);

	val_rot = 0;
}

void AAvion_Mic::Rotire(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	
	val_rot = val_rot + 90;
	
	this->SetActorRotation({ 0, val_rot, 0 });
}

// Called when the game starts or when spawned
void AAvion_Mic::BeginPlay()
{
	Super::BeginPlay();


	
}

// Called every frame
void AAvion_Mic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

