// Copyright Seele

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "SeelePlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

/** PlayerState. The Asc and As live on this thing
 *  As far as I understand this holds all the relevant player information. Like instead of having it directly on the player pawn (like in ALS),
 *	it's on the PlayerState. In case the Pawn dies and is respawned, all the relevant information is still there, because it's kept here. Information about the player that is important to everyone (replicated).
 *	
 */
UCLASS()
class AURA_API ASeelePlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// constructor
	ASeelePlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
