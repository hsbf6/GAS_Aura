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

	//Checking if SeeleAttributeSet is actually valid
	USeeleAttributeSet* SeeleAttributeSet = CastChecked<USeeleAttributeSet>(AttributeSet);
	//Broadcast values to the AS
	OnHealthChanged.Broadcast(SeeleAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(SeeleAttributeSet->GetMaxHealth());


}
