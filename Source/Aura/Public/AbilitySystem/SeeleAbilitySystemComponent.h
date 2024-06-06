// Copyright Seele

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SeeleAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer& /* AssetTags */);

/**
 * 
 */
UCLASS()
class AURA_API USeeleAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
	

public:

	void AbilityActorInfoSet();

	FEffectAssetTags EffectAssetTags;

protected:

	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);


};
