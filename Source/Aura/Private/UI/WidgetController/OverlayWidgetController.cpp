// Copyright Seele


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/SeeleAbilitySystemComponent.h"
#include "AbilitySystem/SeeleAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValue()
{
	// Super::BroadcastInitialValue();   No need to call Super, because it's just an empty function

	//Creating delegates to broadcast the initial values to HUD
	/*My attempt to grab the health variable from the attribute set was this:
	 * float CurrentHealth = AbilitySystemComponent->GetNumericAttribute(USeeleAttributeSet::GetHealthAttribute());
	 *
	 */
	float CurrentHealth = AbilitySystemComponent->GetNumericAttribute(USeeleAttributeSet::GetHealthAttribute());
	// Checking if SeeleAttributeSet is actually valid
	const USeeleAttributeSet* SeeleAttributeSet = CastChecked<USeeleAttributeSet>(AttributeSet);
	/* Broadcast values to the AS
	* When doing quest challenge I forgot to call Broadcast here for Mana,
	* therefore the Mana Globe parameters were not set (initial value 50, bottle adds 25.f)
	* Because these lines set all the initial values
	*/
	OnHealthChanged.Broadcast(SeeleAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(SeeleAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(SeeleAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(SeeleAttributeSet->GetMaxMana());
	

}

void UOverlayWidgetController::BindCallBacksToDependencies()
{
	// Don't need Super, because the parent function is empty
	// Super::BindCallBacksToDependencies();

	// Get the AS call-back functions 
	const USeeleAttributeSet* SeeleAttributeSet = CastChecked<USeeleAttributeSet>(AttributeSet);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		SeeleAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		SeeleAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		SeeleAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		SeeleAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
	
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
