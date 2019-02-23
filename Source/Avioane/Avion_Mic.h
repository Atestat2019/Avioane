#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Avion_Mic.generated.h"

UCLASS()
class AVIOANE_API AAvion_Mic : public AActor
{
	GENERATED_BODY()

public:
	
	AAvion_Mic();

	class AAvioanePawn* acces;

	UPROPERTY(EditAnywhere)
		FVector locinit;

	bool selectat_mic;

	UFUNCTION()
		void Rotire_Mic();

	UFUNCTION()
		void Click_Mic(UPrimitiveComponent * ClickedComp, FKey ButtonClicked);

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere)
		class AAvioaneBlock* obiect_atins;

	UPROPERTY(EditAnywhere)
		class AAvion_Fals* mesh_fals;

	UPROPERTY(EditAnywhere)
		float val_rot;

	UPROPERTY(EditAnywhere)
		int nr;

	UPROPERTY(EditAnywhere)
		class AAvioaneBlockGrid* tabla;

	
protected:

	virtual void BeginPlay() override;

	void Tick(float DeltaTime);
	
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
		void OnOverlapExit(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};