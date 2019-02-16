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

	UFUNCTION()
	void HandleClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	void Evidentiere(bool bOn);

	void Change_Mat(bool bOn);

	class AAvion_Mare* avion_mare;

	class AAvion_Mic* avion_mic;

	static class AAvioanePawn* acces;

	static int k;

	TArray<UMaterialInstance*> materiale;

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
		class UMaterialInstance* Material_Galben;


	UPROPERTY()
		class UMaterialInstance* BlueMaterial;
	UPROPERTY()
		class UMaterialInstance* OrangeMaterial;


	UPROPERTY()
		class AAvioaneBlockGrid* grida;

	UPROPERTY(EditAnywhere)
		bool atins;

	UPROPERTY(EditAnywhere)
		bool ocupat;

public:

	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	FORCEINLINE class UStaticMeshComponent* GetBlockMesh() const { return BlockMesh; }


protected:

	virtual void BeginPlay() override;
};
