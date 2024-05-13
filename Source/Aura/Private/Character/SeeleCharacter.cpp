// Copyright Seele


#include "Character/SeeleCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/SeelePlayerController.h"
#include "Player/SeelePlayerState.h"
#include "UI/HUD/SeeleHUD.h"

ASeeleCharacter::ASeeleCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	

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
{
	ASeelePlayerState* SeelePlayerState = GetPlayerState<ASeelePlayerState>();
	check(SeelePlayerState);
	SeelePlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(SeelePlayerState, this);
	AbilitySystemComponent = SeelePlayerState->GetAbilitySystemComponent();
	AttributeSet = SeelePlayerState->GetAttributeSet();

	if (ASeelePlayerController* SeelePlayerController = Cast<ASeelePlayerController>(GetController()))
	{
		if (ASeeleHUD* SeeleHUD = Cast<ASeeleHUD>(SeelePlayerController->GetHUD()))
		{
			SeeleHUD->InitOverlay(SeelePlayerController, SeelePlayerState, AbilitySystemComponent, AttributeSet);
		}
	}



	/* This might also work. Using a TObjectPtr to grab the class ASeelePlayerController, store it
	 * in a variable called SeelePlayerController and reference it here. BUT TObjectPtr should not
	 * be used in local variables, which SeelePlayerController is in this case.
	 *
	SeelePlayerController = Cast<ASeelePlayerController>(GetController());
	*/
}
 