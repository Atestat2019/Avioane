#include "Test.h"


ATest::ATest()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATest::BeginPlay()
{
	Super::BeginPlay();
}

void ATest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

