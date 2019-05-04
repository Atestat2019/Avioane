#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AvioaneBlock.generated.h"


UCLASS(minimalapi)
class AAvioaneBlock : public AActor
{
	GENERATED_BODY()

public:

	AAvioaneBlock();

	void Evidentiere(bool bOn);

	void Change_Mat(int bOn);

	static int32 nr_mat;

	static bool ok;
	
	static class AAvioaneGameMode* GM;

	static TArray<class UMaterialInstance*> materiale;
	static TArray<class UMaterial*> X_materiale;
	static TArray<class UMaterial*> Motor_materiale;
	static TArray<class UMaterial*> Pilot_materiale;

	UFUNCTION()
		void HandleClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* DummyRoot;

	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* BlockMesh;

	UPROPERTY()
		class UMaterial* BaseMaterial;
	UPROPERTY()
		class UMaterialInstance* Material_Gri;
	UPROPERTY()
		class UMaterialInstance* Material_0;
	UPROPERTY()
		class UMaterial* XGriMaterial;

	UPROPERTY()
		class AAvioaneBlockGrid* acces;

	UPROPERTY(EditAnywhere)
		bool atins;

	UPROPERTY(EditAnywhere)
		bool ocupat;

	UPROPERTY(EditAnywhere)
		int32 nr_culoare;

	UPROPERTY(EditAnywhere)
		int32 lin;

	UPROPERTY(EditAnywhere)
		int32 coln;

	UPROPERTY(EditAnywhere)
		FString tip;

	UPROPERTY(EditAnywhere)
		bool pilot;

	UPROPERTY(EditAnywhere)
		bool motor;

	UPROPERTY(EditAnywhere)
		bool siguranta;

	void Bordare(AAvioaneBlock* patrat);


public:

	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	FORCEINLINE class UStaticMeshComponent* GetBlockMesh() const { return BlockMesh; }


protected:

	virtual void BeginPlay() override;
};
