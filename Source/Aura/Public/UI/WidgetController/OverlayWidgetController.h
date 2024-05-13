// Copyright Seele

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/SeeleWidgetController.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, MaxHealth);



/**
 * 
 */
UCLASS()
class AURA_API UOverlayWidgetController : public USeeleWidgetController
{
	GENERATED_BODY()

public:
	/*This function is declared in the parent class. We call it here to define its values*/
	virtual void BroadcastInitialValue() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;

};
