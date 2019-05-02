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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Jucator_Actual;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Stadiu;

	bool Safe(AAvioaneBlock* patrat, int32 ok_liber);

	void Colorare_Tabla(int32 nr_juc);

	bool Lovitura(AAvioaneBlock* patrat);

	void Schimb_Jucator();

	void Doborare_Avion(int32 k);

	void Final();

	bool safe_margine(int32 i, int32 j);

	int32 ok;

	FString mod_de_joc;
	
	FString sunet;

	FTimerHandle chronos;

	
protected:

	virtual void BeginPlay() override;
};