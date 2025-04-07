// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/AuraHUD.h"

#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/Widgets/AuraUserWidget.h"


// Construct the widget controller, the widget and set the widget controller and add to the viewport
void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	// Create overlay and widget controller
	checkf(OverlayWidgetClass, TEXT("Overlay widget class uninitiazied. please fill out bp aura hud"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay widget controller class uninitiazied. pPleae fill out bp aura hud"));

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);

	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);

	// Tell the widget controller to broadcast its initial values
	WidgetController->BroadcastInitialValues();
	Widget->AddToViewport();
}


// This function retrieves the Overlay Widget Controller, and if it doesn't find one it will call a function to create it
UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);

		// Once we have set the controller params, bind the listen delegates and callbacks for any attribute changes
		OverlayWidgetController->BindCallbacksToDependencies();
	}
	return OverlayWidgetController;
}
	

UAttributeMenuWidgetController* AAuraHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if (AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParams(WCParams);

		// Once we have set the controller params, bind the listen delegates and callbacks for any attribute changes
		AttributeMenuWidgetController->BindCallbacksToDependencies();
	}
	return AttributeMenuWidgetController;
}


