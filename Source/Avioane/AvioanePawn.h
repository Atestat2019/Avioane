#pragma once

#include "CoreMinimal.h"
#include "PlayerInstance.h"
#include "GameFramework/Pawn.h"
#include "AvioanePawn.generated.h"


UCLASS(config = Game)
class AAvioanePawn : public APawn, public PlayerInstance
{
	GENERATED_UCLASS_BODY()

public:

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		AActor* Camera1;

	UPROPERTY(EditAnywhere)
		AActor* Camera2;
	
	UPROPERTY(EditAnywhere)
		AActor* Camera3;

	UFUNCTION()
		void Schimbare_Camera();

	UFUNCTION()
		virtual void Plasare_Avioane() override;
	
	UFUNCTION()
		virtual void intarziere() override;

	UFUNCTION()
		virtual void Tura() override;

	UFUNCTION()
		virtual void Ref() override;

	UPROPERTY(EditAnywhere)
		float timp_s;


protected:

	virtual void BeginPlay() override;

	void TraceForBlock(const FVector& Start, const FVector& End, bool bDrawDebugHelpers);
	
	void Rotire();
	
	void Deblocare();
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		class AAvioaneBlock* CurrentBlockFocus;
};
