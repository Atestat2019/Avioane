#include "Avion_Fals.h"


AAvion_Fals::AAvion_Fals()
{
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
}

void AAvion_Fals::BeginPlay()
{
	Super::BeginPlay();
}

void AAvion_Fals::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

