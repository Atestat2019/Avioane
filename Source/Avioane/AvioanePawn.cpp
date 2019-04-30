#include "AvioanePawn.h"
#include "AvioaneBlock.h"
#include "AvioaneBlockGrid.h"
#include "AvioaneGameMode.h"
#include "Components/BoxComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "Avion.h"
#include "EngineUtils.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/Public/TimerManager.h"
#include "Components/TextRenderComponent.h"


AAvioanePawn::AAvioanePawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	timp_s = 1.5;
	nr_jucator = 0;
	nr_avioane_distruse = 0;
	acces = nullptr;

	for (int32 i = 0; i < 20; i++)
		motoare_distruse[i] = 0;

	for (int32 i = 0; i < 20; i++)
		piloti_doborati[i] = 0;
}

void AAvioanePawn::Plasare_Avioane()
{
	//acces->mesaj->SetText(TEXT("Plaseaza-ti avioanele!"));
	//acces->mesaj->DestroyComponent();

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

void AAvioanePawn::intarziere()
{
	APlayerController* jucator = UGameplayStatics::GetPlayerController(this, 0);

	if (jucator->GetViewTarget() == Camera1)
	{
		GetWorld()->GetTimerManager().SetTimer(chronos, this, &AAvioanePawn::Schimbare_Camera, timp_s, false);
	}
}

void AAvioanePawn::Schimbare_Camera()
{
	APlayerController* jucator = UGameplayStatics::GetPlayerController(this, 0);

	jucator->SetViewTargetWithBlend(Camera2, 1.0f);
	
	GetWorldTimerManager().ClearTimer(chronos);
}

void AAvioanePawn::BeginPlay()
{
	Super::BeginPlay();

	AAvioaneGameMode* GM = GetWorld()->GetAuthGameMode<AAvioaneGameMode>();

	for (TActorIterator<AAvioaneBlockGrid> it(GetWorld()); it; ++it)
	{
		if (it->ActorHasTag("Jucator"))
			acces = *it;
	}

	acces->mesaj->SetText(TEXT("Plaseaza-ti avioanele!"));
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
	for (int i = 0; i < acces->avioane.Num(); i++)
	{
		if (acces->avioane[i]->selectat == true)
			acces->avioane[i]->Rotire();
	}	
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

void AAvioanePawn::Tura()
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Este tura ta!"));

}

