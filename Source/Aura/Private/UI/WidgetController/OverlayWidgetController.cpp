// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"

// broadcast to the hud the initial values using delegates, 
void UOverlayWidgetController::BroadcastInitialValues()
{
	// Get the attribute that was passed into the controller, and fire off the delegate
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());


}
// Delegate that is called every time an attribute is changed
void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	// bind each attribute to a particular callback function
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);

}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	// Tell the widgets bound to onhealthchanged to fire off
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	// Tell the widgets bound to onmaxhealthchanged to fire off
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}
