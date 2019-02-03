// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Avion_Mare.generated.h"

UCLASS()
class AVIOANE_API AAvion_Mare : public AActor
{
	GENERATED_BODY()

		/** Dummy root component */
		UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* DummyRoot;


public:
	AAvion_Mare();

	/** How many blocks have been clicked */
	int32 Score;

	/** Number of blocks along each side of grid */
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
		int32 Size;

	/** Spacing of blocks */
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
		float BlockSpacing;

	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
		float scala_x;
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
		float scala_y;
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
		float scala_z;

	class AAvioaneBlock* tabla[9][9];

protected:
	// Begin AActor interface
	virtual void BeginPlay() override;
	void Tick(float DeltaTime);
	// End AActor interface

public:


	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }

};
