// Fill out your copyright notice in the Description page of Project Settings.

#include "Avion_Mare.h"
#include "AvioaneBlock.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"

// Sets default values
AAvion_Mare::AAvion_Mare()
{
	
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshhhh"));
	mesh->OnClicked.AddDynamic(this, &AAvion_Mare::Rotire);
	mesh->OnComponentBeginOverlap.AddDynamic(this, &AAvion_Mare::OnOverlapBegin);
	val_rot = 0;

	SetActorEnableCollision(true);
	
	
}

	

void AAvion_Mare::Rotire(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{

	val_rot = val_rot + 90;

	this->SetActorRotation({ 0, val_rot, 0 });
}

// Called when the game starts or when spawned
void AAvion_Mare::BeginPlay()
{
	Super::BeginPlay();
	


}

// Called every frame
void AAvion_Mare::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAvion_Mare::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("lalalalal"));
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("lalalalal"));
	}
}

