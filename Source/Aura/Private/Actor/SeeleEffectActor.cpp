// Copyright Seele


#include "Actor/SeeleEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/SeeleAttributeSet.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
//#include <AbilitySystemBlueprintLibrary.h>


ASeeleEffectActor::ASeeleEffectActor()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	// Set Actor root component to simply the result of creating a SceneComponent
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}
	
void ASeeleEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}



/* The whole following section is about applying effects
*  
*/




void ASeeleEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr) return;
	
	// This Effect Actor is specifically designed to apply a effect. If it doesn't have an effect, it misses its purpose, therefore we'll intentionally crash at this point.
	check(GameplayEffectClass);
	/* MakeEffectContext is a way to create the wrapper FGameplayEffectContextHandle, which contains an internal 
	 * FGameplayEffectContext. It's a struct and lives in GameplayEffectTypes.h
	 */
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	//what object caused this GameplayEffect? AddSourceObject function sets this
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.0f, EffectContextHandle);
	// Take the EffectsSpecHandle, take the Data, which is a TSharedPtr, call Get() to get the raw pointer and then lastly dereference with *, because input argument is a const reference, not a pointer.
	const FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());


	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
	}
}











void ASeeleEffectActor::OnOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteEffectRemovalPolicy==EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
}








void ASeeleEffectActor::EndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteEffectRemovalPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
	if (InfiniteEffectRemovalPolicy==EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		// If ASC is not valid, exit the function
		if (!IsValid(TargetASC)) return;
		
		//Store in array to remove later from the Map
		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		for (TPair<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair : ActiveEffectHandles)
		{
			if (TargetASC == HandlePair.Value)
			{
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);
				HandlesToRemove.Add(HandlePair.Key);
			}
		}
		for (FActiveGameplayEffectHandle& Handle : HandlesToRemove)
		{
			ActiveEffectHandles.FindAndRemoveChecked(Handle); // Unreal Function
		}
	}

}



