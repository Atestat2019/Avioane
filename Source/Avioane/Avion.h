#pragma once

#include "CoreMinimal.h"
#include "AvioaneBlock.h"
#include "GameFramework/Actor.h"
#include "Avion.generated.h"

UCLASS()
class AVIOANE_API AAvion : public AActor
{
	GENERATED_BODY()
	
public:	


	AAvion();

	//class AAvioanePawn* acces;

	UPROPERTY(EditAnywhere)
		FVector locinit;

	bool selectat;

	UFUNCTION()
		void Rotire();

	UFUNCTION()
		void Click(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	UFUNCTION()
		void Setare_PS(AAvioaneBlock* patrat);
	
	UFUNCTION()
		void Setare_Material_PS(AAvioaneBlock* patrat, FString tip);

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* mesh;


	UPROPERTY(EditAnywhere)
		class AAvioaneBlock* obiect_atins;

	UPROPERTY(EditAnywhere)
		class AAvioaneBlockGrid* acces;

	UPROPERTY(EditAnywhere)
		class AAvion_Fals* mesh_fals;
	UPROPERTY(EditAnywhere)
		class AAvion_Fals* outline;

	UPROPERTY(EditAnywhere)
		float val_rot;
	UPROPERTY(EditAnywhere)
		int nr;


	FName tag;


protected:


	virtual void BeginPlay() override;

	void Tick(float DeltaTime);

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
		void OnOverlapExit(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
