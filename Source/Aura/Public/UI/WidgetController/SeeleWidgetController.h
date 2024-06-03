// Copyright Seele

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "UObject/NoExportTypes.h"
#include "SeeleWidgetController.generated.h"


// forward declare
class UAttributeSet;
class UAbilitySystemComponent;

/* WidgetController base class.
 * OverlayWidgetController derives from this
 */


// Create a USTRUCT. Created before the main body of the class

USTRUCT(BlueprintType)
struct FWidgetControllerParams	
{
	GENERATED_BODY()
	// Name of our struct declared above

	// empty constructor. Also no []. No idea why.
	FWidgetControllerParams() {}
	FWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS) : PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS) {}

	// Initialize a bunch of the arguments as nullptr. Apparently might throw compile error if not.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
	
};


/**
 * 
 */
UCLASS()
class AURA_API USeeleWidgetController : public UObject
{
	GENERATED_BODY()


public:
	
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& WCParams);
	virtual void BroadcastInitialValue();
	// create function for callback when attribute values change (at the moment only on HealthChanged)
	virtual void BindCallBacksToDependencies();

	
protected:

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;

	
};
