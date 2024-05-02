// Copyright Seele

#pragma once

#include "CoreMinimal.h"
#include "Character/SeeleCharacterBase.h"
#include "SeeleCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API ASeeleCharacter : public ASeeleCharacterBase
{
	GENERATED_BODY()
	
public:
	ASeeleCharacter();

	// Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	// End APawn Interface.

private:
	void InitAbilityActorInfo(); 
};
