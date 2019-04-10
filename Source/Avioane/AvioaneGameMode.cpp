#include "AvioaneGameMode.h"
#include "AvioanePlayerController.h"
#include "AvioanePawn.h"
#include "AIPawn.h"
#include "Engine.h"


AAvioaneGameMode::AAvioaneGameMode()
{
	// no pawn by default
	DefaultPawnClass = AAvioanePawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = AAvioanePlayerController::StaticClass();

	
	
}

void AAvioaneGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	for (TActorIterator<AAvioanePawn> it(GetWorld()); it; ++it)
	{
		Jucatori.Add(*it);
		break;
	}
	for (TActorIterator<AAIPawn> it(GetWorld()); it; ++it)
	{
		Jucatori.Add(*it);
		break;
	}

	for (int32 i = 0; i < Jucatori.Num(); i++)
	{
		Jucatori[i]->nr_jucator = i;
	}

	Jucator_Actual = 0;

	Jucatori[Jucator_Actual]->Plasare_Avioane();
	Jucatori[(Jucator_Actual+1)%Jucatori.Num()]->Plasare_Avioane();
}

