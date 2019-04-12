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
	
	static class AAvioaneGameMode* GM;

	TArray<UMaterialInstance*> materiale;

	UFUNCTION()
		void HandleClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* DummyRoot;

	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* BlockMesh;


	UPROPERTY()
		class UMaterial* BaseMaterial;

	UPROPERTY()
		class UMaterialInstance* Material_Rosu;
	UPROPERTY()
		class UMaterialInstance* Material_Albastru;
	UPROPERTY()
		class UMaterialInstance* Material_Verde;
	UPROPERTY()
		class UMaterialInstance* Material_Lime;


	UPROPERTY()
		class UMaterialInstance* Material_Gri;
	UPROPERTY()
		class UMaterialInstance* Material_Ceapa;


	UPROPERTY()
		class AAvioaneBlockGrid* acces;

	UPROPERTY(EditAnywhere)
		bool atins;

	UPROPERTY(EditAnywhere)
		bool ocupat;

	UPROPERTY(EditAnywhere)
		int32 nr_culoare;

	

public:

	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	FORCEINLINE class UStaticMeshComponent* GetBlockMesh() const { return BlockMesh; }


protected:

	virtual void BeginPlay() override;
};
