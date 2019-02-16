#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AvioaneBlockGrid.generated.h"


UCLASS(minimalapi)
class AAvioaneBlockGrid : public AActor
{
	GENERATED_BODY()

	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

public:
	AAvioaneBlockGrid();

	class AAvioaneBlock* tabla[21][21];

	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
		int32 Size;

	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
		float BlockSpacing;

	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
		float scala_x;
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
		float scala_y;
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
		float scala_z;

	
protected:

	virtual void BeginPlay() override;


public:

	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
};



