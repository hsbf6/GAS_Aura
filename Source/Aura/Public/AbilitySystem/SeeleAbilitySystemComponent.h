// Copyright Seele

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SeeleAbilitySystemComponent.generated.h"



/**
 * 
 */
UCLASS()
class AURA_API USeeleAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
	

public:

	void AbilityActorInfoSet();

protected:

	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);


};
