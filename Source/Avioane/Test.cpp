#include "Test.h"


ATest::ATest()
{
	PrimaryActorTick.bCanEverTick = true;

	/*
	CustomMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Test Component"));
	CustomMeshComponent->OnBeginCursorOver.AddDynamic(this, &ATest::CustomOnBeginMouseOver);
	*/
}

void ATest::CustomOnBeginMouseOver(UPrimitiveComponent * TouchedComponent)
{
	/*
	if (GEngine)
	{
		UE_LOG(LogTemp, Warning, TEXT("aici?"));
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, TEXT("Mouse Over"));
	}
	UE_LOG(LogTemp, Warning, TEXT("aici?"));
	*/
}


void ATest::BeginPlay()
{
	Super::BeginPlay();
}

void ATest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

