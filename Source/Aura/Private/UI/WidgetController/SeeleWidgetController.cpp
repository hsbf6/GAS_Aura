// Copyright Seele


#include "UI/WidgetController/SeeleWidgetController.h"

/* WidgetController base class.
 * OverlayWidgetController derives from this
 */

void USeeleWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{

	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;

}

void USeeleWidgetController::BroadcastInitialValue()
{

}

void USeeleWidgetController::BindCallBacksToDependencies()
{

}
