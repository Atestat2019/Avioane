#include "AvioanePawn.h"
#include "AvioaneBlock.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Avion_Mare.h"
#include "Avion_Mic.h"
#include "EngineUtils.h"

AAvioanePawn::AAvioanePawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	este_avion_selectat = false;
}

void AAvioanePawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UCameraComponent* OurCamera = PC->GetViewTarget()->FindComponentByClass<UCameraComponent>())
			{
				FVector Start = OurCamera->GetComponentLocation();
				FVector End = Start + (OurCamera->GetComponentRotation().Vector() * 8000.0f);
				TraceForBlock(Start, End, true);
			}
		}
		else
		{
			FVector Start, Dir, End;
			PC->DeprojectMousePositionToWorld(Start, Dir);
			End = Start + (Dir * 8000.0f);
			TraceForBlock(Start, End, true);
		}
	}

}

void AAvioanePawn::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<AAvion_Mare> it(GetWorld()); it; ++it)
	{
		avion_mare = *it;
	}
	for (TActorIterator<AAvion_Mic> it(GetWorld()); it; ++it)
	{
		avioane_mici.Add(*it);
	}
}

void AAvioanePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Rotire", EInputEvent::IE_Pressed, this, &AAvioanePawn::Rotire);
}

void AAvioanePawn::CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult)
{
	Super::CalcCamera(DeltaTime, OutResult);

	OutResult.Rotation = FRotator(-90.0f, -90.0f, 0.0f);
}




void AAvioanePawn::Rotire()
{
	if (avion_mare != nullptr)
	{
		if (avion_mare->selectat_mare == true)
			avion_mare->Rotire_Mare();
	}
	for (int i = 0; i < avioane_mici.Num(); i++)
	{
		if (avioane_mici[i]->selectat_mic == true)
			avioane_mici[i]->Rotire_Mic();
	}

	//UE_LOG(LogTemp, Warning, TEXT("poate aici?"));	
}

void AAvioanePawn::TraceForBlock(const FVector& Start, const FVector& End, bool bDrawDebugHelpers)
{
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);
	if (bDrawDebugHelpers)
	{
		DrawDebugLine(GetWorld(), Start, HitResult.Location, FColor::Red);
		DrawDebugSolidBox(GetWorld(), HitResult.Location, FVector(20.0f), FColor::Red);

		//UE_LOG(LogTemp, Warning, TEXT("Locatie1: %s"), *Start.ToString());
		//UE_LOG(LogTemp, Warning, TEXT("Locatie2: %s"), *End.ToString());
	}
	if (HitResult.Actor.IsValid())
	{
		AAvioaneBlock* HitBlock = Cast<AAvioaneBlock>(HitResult.Actor.Get());
		if (CurrentBlockFocus != HitBlock)
		{
			if (CurrentBlockFocus)
			{
				CurrentBlockFocus->Evidentiere(false);
			}
			if (HitBlock)
			{
				HitBlock->Evidentiere(true);
			}
			CurrentBlockFocus = HitBlock;
		}
	}
	else if (CurrentBlockFocus)
	{
		CurrentBlockFocus->Evidentiere(false);
		CurrentBlockFocus = nullptr;
	}
}