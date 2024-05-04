// Copyright Seele


#include "UI/Widget/SeeleUserWidget.h"

void USeeleUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
