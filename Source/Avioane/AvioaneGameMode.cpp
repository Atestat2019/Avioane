#include "AvioaneGameMode.h"
#include "AvioanePlayerController.h"
#include "AvioanePawn.h"
#include "Engine.h"


AAvioaneGameMode::AAvioaneGameMode()
{
	// no pawn by default
	DefaultPawnClass = AAvioanePawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = AAvioanePlayerController::StaticClass();

	//Pawn = Cast<AAvioanePawn>(*GetWorld()->GetPawnIterator());
	
	
}

void AAvioaneGameMode::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<AAvioanePawn> it(GetWorld()); it; ++it)
	{
		Pawn = *it;
		break;
	}

}

