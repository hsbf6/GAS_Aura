// Copyright Seele


#include "Player/SeelePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "DrawDebugHelpers.h"
#include "Interaction/EnemyInterface.h"

ASeelePlayerController::ASeelePlayerController()
{
	bReplicates = true;
}

void ASeelePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// Call function CursorTrace. Trace every frame.
	CursorTrace();

	
}

void ASeelePlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
		if (!CursorHit.bBlockingHit) return;

	/* This is casting to the interface to see if anyone of the hit actors implements it. Enemy does in fact implement it.
	 * However, there was an issue with the 'ThisActor =' assignment. If EnemyInterface implementation in the header file is NOT a raw pointer but instead a TScriptInterface it does not work
	 */
		LastActor = ThisActor;
		ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());
		

	/**
	 * Line trace from cursor. There are several scenarios:
	 * A. LastActor is null && ThisActor is null
	 *		- Do nothing
	 * B. LastActor is null && ThisActor is valid
	 *		- Highlight ThisActor
	 * C. LastActor is valid && ThisActor is null
	 *		- UnHighlight LastActor
	 * D. Both actors are valid, but LastActor != ThisActor
	 *		- UnHighlight LastActor, and Highlight ThisActor
	 * E. Both actors are valid and are the same actor
	 *		- Do nothing
	 */

		
		if (LastActor == nullptr) //This could be option A or B now
		{
			if (ThisActor != nullptr) //If ThisActor is NOT null, then it's option B
			{
				//Case B; That means we have to call Highlight on this actor
				ThisActor->HighlightActor();
			}
			else
			{
				//Case A; both are null, do nothing
			}

		}
		else //LastActor is valid
		{
			if (ThisActor == nullptr)
			{
				//Case C; we UnHighlight the LastActor
				LastActor->UnHighlightActor();
			}
			else //both actors are valid
			{
				if (LastActor != ThisActor)
				{
					//Case D; UnHighlight LastActor and Highlight ThisActor
					LastActor->UnHighlightActor();
					ThisActor->HighlightActor();
				}
				else
				{
					//Case E; both are valid. Do nothing
				}
			}
		
		}
}

void ASeelePlayerController::BeginPlay()
{
	Super::BeginPlay(); 
	check(SeeleContext);

	/* Add input mapping context. This used to be an asser check(). BUT changed after implementing GAS. That's because in
	 * multiplayer there might be other local players that don't have a valid player controller, because only the server
	 * has all player controllers.
	 * Meaning the game would crash.
	 */
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(SeeleContext, 0);
	}
	

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void ASeelePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// CastChecked means it cannot be null. If null then crash. 
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
		
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASeelePlayerController::Move);

}

void ASeelePlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}


