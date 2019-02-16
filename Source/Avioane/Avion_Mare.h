#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AvioanePawn.h"
#include "Avion_Mare.generated.h"


UCLASS()
class AVIOANE_API AAvion_Mare : public AActor
{
	GENERATED_BODY()

public:
	
	AAvion_Mare();
	
	class AAvioanePawn* acces;

	bool selectat_mare;

	UFUNCTION()
		void Rotire_Mare();

	UFUNCTION()
		void Click_Mare(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere)
		class AAvioaneBlock* obiect_atins;
	
	UPROPERTY(EditAnywhere)
		class AAvion_Fals* mesh_fals;

	UPROPERTY(EditAnywhere)
		float val_rot;


protected:
	
	virtual void BeginPlay() override;

	void Tick(float DeltaTime);
	
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
		void OnOverlapExit(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};