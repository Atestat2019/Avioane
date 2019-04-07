#include "Test.h"
#include "Engine/Engine.h"
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


ATest::ATest()
{
	PrimaryActorTick.bCanEverTick = true;

	CustomMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Test Component"));
	CustomMeshComponent->OnBeginCursorOver.AddDynamic(this, &ATest::CustomOnBeginMouseOver);
}

void ATest::CustomOnBeginMouseOver(UPrimitiveComponent * TouchedComponent)
{
	if (GEngine)
	{
		UE_LOG(LogTemp, Warning, TEXT("aici?"));
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, TEXT("Mouse Over"));
	}
	UE_LOG(LogTemp, Warning, TEXT("aici?"));
}

void ATest::BeginPlay()
{
	Super::BeginPlay();
}

void ATest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

