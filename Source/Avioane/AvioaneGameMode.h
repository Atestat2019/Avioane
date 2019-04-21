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

	//FTimerHandle chronos;

	int32 Jucator_Actual;

	int32 Stadiu;

	virtual bool Safe(AAvioaneBlock* patrat);

	virtual void Colorare_Tabla(int32 nr_juc);

	virtual bool Lovitura(AAvioaneBlock* patrat);

	virtual void Schimb_Jucator();

	virtual void Doborare_Avion(int32 k);

	virtual void Final();

	bool ok;

protected:

	virtual void BeginPlay() override;
};