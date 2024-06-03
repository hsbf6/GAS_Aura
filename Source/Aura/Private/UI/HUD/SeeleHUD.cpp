// Copyright Seele


#include "UI/HUD/SeeleHUD.h"

#include "Components/Overlay.h"
#include "UI/Widget/SeeleUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"


//    OverlayWidgetController is constructed here by the HUD
UOverlayWidgetController* ASeeleHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		// Set Widget Controller parameters. We know that key variables are set now
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallBacksToDependencies();

		return OverlayWidgetController;
	}
	return OverlayWidgetController;

}

void ASeeleHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class unitialized, please fill out BP_AuraHUD"));

	// create the widget
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<USeeleUserWidget>(Widget);

	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	/* create widget controller
	*  at this point the controller has a valid attribute set, because we are passing in
	*  WidgetControllerParams
	*/
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	/* Widget Controller on OverlayWidget
	*  set widget controller to the result of GetOverlayWidgetController()
	*  widgetControllerSet Blueprint event will be called at this point
	*/
	OverlayWidget->SetWidgetController(WidgetController);
	// Right after this we tell the widget controller to broadcast its initial values
	WidgetController->BroadcastInitialValue();
	Widget->AddToViewport();
}


