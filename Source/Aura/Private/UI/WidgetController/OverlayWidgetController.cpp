// Copyright Seele


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/SeeleAbilitySystemComponent.h"
#include "AbilitySystem/SeeleAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValue()
{
	// Super::BroadcastInitialValue();   No need to call Super, because it's just an empty function

	// Creating delegates to broadcast the initial values to HUD
	float CurrentHealth = AbilitySystemComponent->GetNumericAttribute(USeeleAttributeSet::GetHealthAttribute());
	// Checking if SeeleAttributeSet is actually valid
	const USeeleAttributeSet* SeeleAttributeSet = CastChecked<USeeleAttributeSet>(AttributeSet);
	// Broadcast values to the AS
	 
	OnHealthChanged.Broadcast(SeeleAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(SeeleAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(SeeleAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(SeeleAttributeSet->GetMaxMana());
	

}

void UOverlayWidgetController::BindCallBacksToDependencies()
{
	// Don't need Super, because the parent function is empty
	// Super::BindCallBacksToDependencies();

	// Get the native ASC call-back functions 
	const USeeleAttributeSet* SeeleAttributeSet = CastChecked<USeeleAttributeSet>(AttributeSet);





	/*Getting multicast delegate(NOT dynamic).Signature can be found if following function and checking type 
	 *These are all delegate callback functions
	 */
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		SeeleAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		SeeleAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		SeeleAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		SeeleAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
	









	/* Lambda - Anonymous function.When broadcast happens in SeeleASC this Lambda will be called
	 * This doesn't require a callback function
	 */
	Cast<USeeleAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
	[] /* input parameter in () */ (const FGameplayTagContainer& AssetTags) 
		{
			for (const FGameplayTag& Tag : AssetTags /* Used to be called TagContainer while residing in SeeleASC */)
			{
				// Takes each Tag in AssetTags and adds OnScreenDebugMessage
				const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue, Msg);

			}
		}

	);
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
