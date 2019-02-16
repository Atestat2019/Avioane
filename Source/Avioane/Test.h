#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Test.generated.h"

UCLASS()
class AVIOANE_API ATest : public AActor
{
	GENERATED_BODY()
	
public:	

	ATest();

protected:

	virtual void BeginPlay() override;


public:	

	virtual void Tick(float DeltaTime) override;
};
