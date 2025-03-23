// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

// broadcast to the hud the initial values using delegates, 
void UOverlayWidgetController::BroadcastInitialValues()
{
	// Get the attribute that was passed into the controller, and fire off the delegate
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
	
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

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);

	// bind a lambda function to the EffectAssetTags delegate on the ability system component
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		// this is the signature for a lamba function (which is an anonymous function)
		[](const FGameplayTagContainer& AssetTags)
		{
			// broadcast to our gameplay controller for all of the tags in the gameplay controller
			for (const FGameplayTag& Tag : AssetTags)
			{
				const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 8, FColor::Blue, Msg );
			}
		}
	);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	// Tell the callback bound to onhealthchanged to fire off
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	// Tell the callback bound to onmaxhealthchanged to fire off
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	// Tell the callback  bound to OnManaChanged to fire off
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	// Tell the callback  bound to OnManaChanged to fire off
	OnMaxManaChanged.Broadcast(Data.NewValue);
}

