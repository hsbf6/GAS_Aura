// Copyright Seele

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "SeeleAttributeSet.generated.h"

// This is from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


/**
 * 
 */
UCLASS()
class AURA_API USeeleAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	USeeleAttributeSet();

	// Returns the properties used for network replication, this needs to be overridden by all actor classes with native replicated properties
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// GAS attributeSet variables are of type FGameplayAttributeData

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	//Create a variable of type FGameplayAttributeData and name Health
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(USeeleAttributeSet, Health);


	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	//Create a variable of type FGameplayAttributeData and name MaxHealth
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(USeeleAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(USeeleAttributeSet, Mana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(USeeleAttributeSet, MaxMana);



	UFUNCTION()
	//create custom function for on replicated for health
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UFUNCTION()
	//create custom function for on replicated for MaxHealth
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	UFUNCTION()
	//create custom function for on replicated for Mana
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	UFUNCTION()
	//create custom function for on replicated for MaxMana
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

	

};
