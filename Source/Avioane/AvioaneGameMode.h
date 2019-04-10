#pragma once

#include "CoreMinimal.h"
#include "PlayerInstance.h"
#include "GameFramework/GameModeBase.h"
#include "AvioaneGameMode.generated.h"


UCLASS(minimalapi)
class AAvioaneGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AAvioaneGameMode();

	TArray<PlayerInstance*> Jucatori;

	int32 Jucator_Actual;

protected:

	virtual void BeginPlay() override;
};
