#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Avion_Fals.generated.h"

UCLASS()
class AVIOANE_API AAvion_Fals : public AActor
{
	GENERATED_BODY()
	
public:	

	AAvion_Fals();

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* mesh;


protected:

	virtual void BeginPlay() override;


public:	

	virtual void Tick(float DeltaTime) override;
};
