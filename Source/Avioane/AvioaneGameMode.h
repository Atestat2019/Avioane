#pragma once

#include "CoreMinimal.h"
#include "PlayerInstance.h"
#include "AvioaneBlockGrid.h"
#include "AvioaneBlock.h"
#include "GameFramework/GameModeBase.h"
#include "AvioaneGameMode.generated.h"


UCLASS(minimalapi)
class AAvioaneGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AAvioaneGameMode();

	TArray<PlayerInstance*> Jucatori;

	TArray<AAvioaneBlockGrid*> gride;

	int32 Jucator_Actual;

	int32 Stadiu;

	bool Safe(AAvioaneBlock* patrat);

	void Colorare_Tabla(int32 nr_juc);

	bool Lovitura(AAvioaneBlock* patrat);

	void Schimb_Jucator();

	void Final();

protected:

	virtual void BeginPlay() override;
};