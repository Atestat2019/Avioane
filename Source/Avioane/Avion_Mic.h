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

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere)
		class AAvioaneBlock* obiect_atins;

	UPROPERTY(EditAnywhere)
		float val_rot;

	UFUNCTION()
		void Rotire_Mic();

	UFUNCTION()
		void Click_Mic(UPrimitiveComponent * ClickedComp, FKey ButtonClicked);

	class AAvioanePawn* acces_selectat;

	bool selectat_mic;


protected:

	virtual void BeginPlay() override;
	void Tick(float DeltaTime);
	
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		void OnOverlapExit(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};