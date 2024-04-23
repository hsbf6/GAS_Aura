// Copyright Seele


#include "Player/SeelePlayerState.h"
#include "AbilitySystem/SeeleAbilitySystemComponent.h"
#include "AbilitySystem/SeeleAttributeSet.h"

ASeelePlayerState::ASeelePlayerState()
{
	//Define ASC and AS. Same way as in Enemy
	AbilitySystemComponent = CreateDefaultSubobject<USeeleAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<USeeleAttributeSet>("AttributeSet");

	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* ASeelePlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
