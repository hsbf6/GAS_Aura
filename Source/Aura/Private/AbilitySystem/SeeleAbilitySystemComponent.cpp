// Copyright Seele


#include "AbilitySystem/SeeleAbilitySystemComponent.h"
#include <AbilitySystemComponent.h>

void USeeleAbilitySystemComponent::AbilityActorInfoSet()
{
	// Binding Delegate here
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &USeeleAbilitySystemComponent::EffectApplied);
}

void USeeleAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	// GEngine->AddOnScreenDebugMessage(1, 8.f, FColor::Cyan, FString("Effect Applied!"));

	/* EffectSpec.GetAllGrantedTags(FGameplayTagContainer & test);
	 * GrantedTags only work on duration based GEs
	 */

	FGameplayTagContainer TagContainer; 
	EffectSpec.GetAllAssetTags(TagContainer);

	for (const FGameplayTag& Tag : TagContainer)
	{
		 // TODO: Broadcast the Tag to the WidgetController
		const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue, Msg);

	}


}

