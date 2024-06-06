// Copyright Seele

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/SeeleWidgetController.h"
#include "OverlayWidgetController.generated.h"


class USeeleUserWidget;
// Found in DelegateCombinations.h; Arguments: (DelegateName, Param1, Param2) 
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, NewMaxMana);

USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase // inherits from the base class for row structures for DataTables
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag(); // Initialize to empty tag

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText(); // Display text to the user in the form of a widget

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<USeeleUserWidget> MessageWidget; // Add a widget so that we could display a little health icon of sorts when pickup

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr; // Pointer to texture to show a picture

};
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public USeeleWidgetController
{
	GENERATED_BODY()

public:
	/*This function is declared in the parent class. We call it here to define its values*/
	virtual void BroadcastInitialValue() override;
	virtual void BindCallBacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnManaChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxManaChangedSignature OnMaxManaChanged;

	

protected:

	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
	void ManaChanged(const FOnAttributeChangeData& Data) const;
	void MaxManaChanged(const FOnAttributeChangeData& Data) const;

	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);

	// This is exposed and can be set in Blueprints
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WidgetData")
	TObjectPtr<UDataTable> MessageWidgetDataTable;
	

};

template<typename T>
inline T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	/*
	T* Row = DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
	if (Row)
	{
		return Row;
	}
	return nullptr;
	* This whole shebang of code is the same as just this line
	*/

	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}
