#pragma once

#include "CoreMinimal.h"
#include "PlayerInstance.h"
#include "AvioaneBlockGrid.h"
#include "GameFramework/GameModeBase.h"
#include "AvioaneGameMode.generated.h"


UCLASS(minimalapi)
class AAvioaneGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AAvioaneGameMode();

	TArray<PlayerInstance*> Jucatori;

	TArray<AAvioaneBlockGrid*> table;

	int32 Jucator_Actual;

	void Colorare_Tabla(int32 nr_juc);

protected:

	virtual void BeginPlay() override;
};
