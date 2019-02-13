// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AvioaneBlock.generated.h"

/** A block that can be clicked */
UCLASS(minimalapi)
class AAvioaneBlock : public AActor
{
	GENERATED_BODY()

	

public:
	AAvioaneBlock();

	
	/** Dummy root component */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* DummyRoot;

	/** StaticMesh component for the clickable block */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* BlockMesh;
	
	/** Are we currently active? */
	bool bIsActive;

	UPROPERTY(EditAnywhere)
	bool atins;

	UPROPERTY(EditAnywhere)
		bool ocupat;


	/** Pointer to white material used on the focused block */
	UPROPERTY()
		class UMaterial* BaseMaterial;

	/** Pointer to blue material used on inactive blocks */
	UPROPERTY()
		class UMaterialInstance* BlueMaterial;

	/** Pointer to orange material used on active blocks */
	UPROPERTY()
		class UMaterialInstance* OrangeMaterial;

	UPROPERTY()
		class UMaterialInstance* Material_Rosu;
	UPROPERTY()
		class UMaterialInstance* Material_Albastru;
	UPROPERTY()
		class UMaterialInstance* Material_Verde;
	UPROPERTY()
		class UMaterialInstance* Material_Galben;

	TArray<UMaterialInstance*> materiale;

	/** Grid that owns us */
	UPROPERTY()
	class AAvioaneBlockGrid* OwningGrid;

	/** Handle the block being clicked */
	UFUNCTION()
	void BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	/** Handle the block being touched  */
	UFUNCTION()
	void OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

	void HandleClicked();

	void Highlight(bool bOn);

	void Change_Mat(bool bOn);

	class AAvion_Mare* avion_mare;

	class AAvion_Mic* avion_mic;

	static int i;


public:
	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	/** Returns BlockMesh subobject **/
	FORCEINLINE class UStaticMeshComponent* GetBlockMesh() const { return BlockMesh; }
};



