#pragma once

#include "CoreMinimal.h"
#include "Avion.h"
#include "GameFramework/Actor.h"
#include "AvioaneBlockGrid.generated.h"


UCLASS(minimalapi)
class AAvioaneBlockGrid : public AActor
{
	GENERATED_BODY()

	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* DummyRoot;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* box;


public:
	AAvioaneBlockGrid();

	UFUNCTION()
		void Evidentiere_Blocuri(int ok);

	UFUNCTION()
		void OnCursorOver(UPrimitiveComponent* Component);

	UFUNCTION()
		void EndCursorOver(UPrimitiveComponent* Component);

	class AAvioaneBlock* tabla[21][21];

	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
		int32 nr_cuburi;

	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
		float dist;

	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
		float scala_x;
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
		float scala_y;
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
		float scala_z;

	TArray<AAvion*> avioane;

	int frecv[20];

	UPROPERTY(EditAnywhere)
		bool este_avion_selectat;

	UPROPERTY(EditAnywhere)
		bool merge_pus;

	UPROPERTY(EditAnywhere)
		int contor_avioane;

	UPROPERTY(EditAnywhere)
		class AAmbientSound* sunet;

	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UTextRenderComponent* mesaj;
	
protected:

	virtual void BeginPlay() override;


public:

	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
};



