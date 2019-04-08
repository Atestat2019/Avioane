#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AvioaneGameMode.generated.h"


UCLASS(minimalapi)
class AAvioaneGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AAvioaneGameMode();

	class AAvioanePawn* Pawn;


protected:

	virtual void BeginPlay() override;
};



