// Copyright Seele


#include "Character/SeeleCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/SeelePlayerController.h"
#include "Player/SeelePlayerState.h"

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

void ASeeleCharacter::InitAbilityActorInfo()
{
	ASeelePlayerState* SeelePlayerState = GetPlayerState<ASeelePlayerState>();
	check(SeelePlayerState);

	SeelePlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(SeelePlayerState, this);
	AbilitySystemComponent = SeelePlayerState->GetAbilitySystemComponent();
	AttributeSet = SeelePlayerState->GetAttributeSet();
}
