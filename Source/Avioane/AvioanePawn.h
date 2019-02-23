#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Avion_Mic.h"
#include "AvioanePawn.generated.h"


UCLASS(config = Game)
class AAvioanePawn : public APawn
{
	GENERATED_UCLASS_BODY()

public:

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult) override;

	class AAvion_Mare* avion_mare;

	TArray<AAvion_Mic*> avioane_mici;
	
	UPROPERTY(EditAnywhere)
		bool este_avion_selectat;

	UPROPERTY(EditAnywhere)
		bool merge_pus;


protected:

	virtual void BeginPlay() override;

	void TraceForBlock(const FVector& Start, const FVector& End, bool bDrawDebugHelpers);
	
	void Rotire();

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		class AAvioaneBlock* CurrentBlockFocus;
};
