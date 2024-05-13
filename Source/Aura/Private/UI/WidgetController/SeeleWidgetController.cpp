// Copyright Seele


#include "UI/WidgetController/SeeleWidgetController.h"


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
