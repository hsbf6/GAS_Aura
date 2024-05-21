// Copyright Seele

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SeeleUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API USeeleUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// This is called in SeeleHUD.cpp 
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:
		UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();

};
