// Copyright Seele

#pragma once

#include "CoreMinimal.h"
#include "Character/SeeleCharacterBase.h"
// #include "Player/SeelePlayerController.h"
#include "SeeleCharacter.generated.h"

/** This is the main player character class. It's derived from CharacterBase.
 *  Initialize networked GAS implementation
 */
UCLASS()
class AURA_API ASeeleCharacter : public ASeeleCharacterBase
{
	GENERATED_BODY()
	
public:
	ASeeleCharacter();

	/* Begin APawn Interface.
	 * InitAbilityActorInfo is called in this function
	*/
	virtual void PossessedBy(AController* NewController) override;
	// Replication for networked game. InitAbilityActorInfo is also called in this function
	virtual void OnRep_PlayerState() override;

	// End APawn Interface.

	/*UPROPERTY()
	TObjectPtr<ASeelePlayerController> SeelePlayerController; 
	*/

private:
	//GAS Initializer. Unreal Engine native function found in \Source\GameplayAbilities\Private\AbilitySystemComponent_Abilities.cpp
	void InitAbilityActorInfo(); 
};
