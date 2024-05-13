// Copyright Seele

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameFramework/HUD.h"
#include "SeeleHUD.generated.h"

struct FWidgetControllerParams;
class USeeleUserWidget;
class UOverlayWidgetController;
class UAbilitySystemComponent;


/**
 * 
 */
UCLASS()
class AURA_API ASeeleHUD : public AHUD
{
	GENERATED_BODY()

public:
	/*Create a USeeleUserWidget pointer of name OverlayWidget
	 *OverlayWidget is not a class of its own, just a variable name
	 */
	UPROPERTY()
	TObjectPtr<USeeleUserWidget> OverlayWidget;

	/*Because we forward declared at the top, we can access the function GetOverlayWidgetController
	 * Because this is now a pointer in the 'normal' C++ sense, we need the & to get a reference to FWidgetControllerParams
	 */
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	/*Initialize overlay of widget. Pass in parameters from struct FWidgetControllerParams
	 *Struct is defined in SeeleWidgetController.h
	 */
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

protected:
		

private:

	// Create local variable version of SeeleUserWidget. Declare it's a subclass of USeeleUserWidget
	UPROPERTY(EditAnywhere)
	TSubclassOf<USeeleUserWidget> OverlayWidgetClass;

	/*Get a reference to OverlayWidgetController.
	 *This only works if forward declared class UOverlayWidgetController
	 */
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	/*Get a reference to the OverlayControllerClass*/
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

};
