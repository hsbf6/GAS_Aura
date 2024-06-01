// Copyright Seele


#include "AbilitySystem/SeeleAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Net/UnrealNetwork.h"
#include "../../../../Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/AttributeSet.h"



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
	Super::PreAttributeChange(Attribute, NewValue);

	
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



void USeeleAttributeSet::SetEffectProperties(const struct FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	// Source = causer of the effect, Target = target of the effect (owner of this AttributeSet)
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	


	// Lots of info from the SOURCE
	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}



// Executed AFTER a gameplay effect changes an attribute
void USeeleAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data); 
	
	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	



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
