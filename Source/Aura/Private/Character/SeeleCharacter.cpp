// Copyright Seele


#include "Character/SeeleCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/SeelePlayerController.h"
#include "Player/SeelePlayerState.h"
#include "UI/HUD/SeeleHUD.h"
#include <AbilitySystem/SeeleAbilitySystemComponent.h>

ASeeleCharacter::ASeeleCharacter() //constructor
{
	// Set a few variables related to player movement. Some only apply because top-down game. Would not apply to third person game.
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
	// I think this is related to orienting the character in accordance with mouse movement
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	
}

void ASeeleCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for the server
	InitAbilityActorInfo();

}

void ASeeleCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//init ability actor info for the client
	InitAbilityActorInfo();

}


// GAS initializer function. Called by PossessedBy and OnRep_PlayerState()
void ASeeleCharacter::InitAbilityActorInfo()
{	// Create local variable SeelePlayerState of type ASeelePlayerState pointer.
	ASeelePlayerState* SeelePlayerState = GetPlayerState<ASeelePlayerState>();
	// Assert. If player state is null, engine will crash.
	check(SeelePlayerState);
	// Get the ASC and call function InitAbilityActorInfo. Determine who's owner and who's avatar.
	SeelePlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(SeelePlayerState, this);

	Cast<USeeleAbilitySystemComponent>(SeelePlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	// ASC TObjectPtr declared but not defined in the base class (SeeleCharacterBase)
	AbilitySystemComponent = SeelePlayerState->GetAbilitySystemComponent();
	// AS TObjectPtr declared but not defined in the base class (SeeleCharacterBase)
	AttributeSet = SeelePlayerState->GetAttributeSet();
	// If player controller is indeed ASeelePlayerController
	if (ASeelePlayerController* SeelePlayerController = Cast<ASeelePlayerController>(GetController()))
	{	// if HUD is ASeeleHUD
		if (ASeeleHUD* SeeleHUD = Cast<ASeeleHUD>(SeelePlayerController->GetHUD()))
		{
			SeeleHUD->InitOverlay(SeelePlayerController, SeelePlayerState, AbilitySystemComponent, AttributeSet);
		}
	}



	
}
 