// Copyright Seele


#include "AbilitySystem/SeeleAttributeSet.h"
#include "AttributeSet.h"
#include "GameFramework/Character.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Net/UnrealNetwork.h"
//#include <UObject/CoreNetTypes.h>


USeeleAttributeSet::USeeleAttributeSet()
{
	InitHealth(50.f);
	InitMaxHealth(100.f);
	InitMana(10.f);
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


// Epic recommends to only use this function for clamping
// Executed JUST before a change in Attribute takes place
void USeeleAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}




/*
* This was test code. Check if system works, print to console to confirm. 
* Clamping not needed for MaxHealth and MaxMana

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
		UE_LOG(LogTemp, Warning, TEXT("Health: %f"), NewValue);

	}
	if (Attribute == GetMaxHealthAttribute())
	{
		UE_LOG(LogTemp, Warning, TEXT("MaxHealth: %f"), NewValue);

	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
		UE_LOG(LogTemp, Warning, TEXT("Mana: %f"), NewValue);

	}
	if (Attribute == GetMaxManaAttribute())
	{
		UE_LOG(LogTemp, Warning, TEXT("MaxMana: %f"), NewValue);

	}


	*/  
	// PreAttributeChange test setup with logging to output log
}









// Executed AFTER a gameplay effect changes an attribute
void USeeleAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	// Source = causer of the effect, Target = target of the effect (owner of this AttributeSet)
	const FGameplayEffectContextHandle EffectContextHandle = Data.EffectSpec.GetContext();
	const UAbilitySystemComponent* SourceASC = EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();


	// Lots of info from the SOURCE
	if (IsValid(SourceASC) && SourceASC->AbilityActorInfo.IsValid() && SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		AActor* SourceAvatarActor = SourceASC->AbilityActorInfo->AvatarActor.Get();
		const AController* SourceController = SourceASC->AbilityActorInfo->PlayerController.Get();
		if (SourceController == nullptr && SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(SourceAvatarActor))
			{
				SourceController = Pawn->GetController();
			}
		}
		if (SourceController)
		{
			ACharacter* SourceCharacter = Cast<ACharacter>(SourceController->GetPawn());
		}
	}
		
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		AActor* TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		AController* TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		ACharacter* TargetCharacter = Cast<ACharacter>(TargetAvatarActor);
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetAvatarActor);
	}
		






	/*
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		
		UE_LOG(LogTemp, Warning, TEXT("Health from GetHealth() : %f"), GetHealth());
		UE_LOG(LogTemp, Warning, TEXT("Magnitude : %f"), Data.EvaluatedData.Magnitude); // How much is the health changing
		
	}
	*/
}









void USeeleAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	// Macro . Multiplayer prediction client-side
	GAMEPLAYATTRIBUTE_REPNOTIFY(USeeleAttributeSet, Health, OldHealth);
}



void USeeleAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	// Multiplayer prediction client-side
	GAMEPLAYATTRIBUTE_REPNOTIFY(USeeleAttributeSet, MaxHealth, OldMaxHealth);
}



void USeeleAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	// Multiplayer prediction client-side
		GAMEPLAYATTRIBUTE_REPNOTIFY(USeeleAttributeSet, Mana, OldMana);
}



void USeeleAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	// Multiplayer prediction client-side
		GAMEPLAYATTRIBUTE_REPNOTIFY(USeeleAttributeSet, MaxMana, OldMaxMana);
}
