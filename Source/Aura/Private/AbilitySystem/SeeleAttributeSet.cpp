// Copyright Seele


#include "AbilitySystem/SeeleAttributeSet.h"
#include "Net/UnrealNetwork.h"

USeeleAttributeSet::USeeleAttributeSet()
{
	InitHealth(50.f);
	InitMaxHealth(100.f);
	InitMana(50.f);
	InitMaxMana(50.f);
}

void USeeleAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(USeeleAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USeeleAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USeeleAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USeeleAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);

}

void USeeleAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	// Multiplayer predicition client-side
	GAMEPLAYATTRIBUTE_REPNOTIFY(USeeleAttributeSet, Health, OldHealth);
}

void USeeleAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	// Multiplayer predicition client-side
	GAMEPLAYATTRIBUTE_REPNOTIFY(USeeleAttributeSet, MaxHealth, OldMaxHealth);
}

void USeeleAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	// Multiplayer predicition client-side
		GAMEPLAYATTRIBUTE_REPNOTIFY(USeeleAttributeSet, Mana, OldMana);
}

void USeeleAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	// Multiplayer predicition client-side
		GAMEPLAYATTRIBUTE_REPNOTIFY(USeeleAttributeSet, MaxMana, OldMaxMana);
}
