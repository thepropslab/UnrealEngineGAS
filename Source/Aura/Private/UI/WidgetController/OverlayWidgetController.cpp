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

	// bind each attribute to a particular callback lambda function - it must have this signature
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetHealthAttribute()).AddLambda(
[this](const FOnAttributeChangeData& Data)
			{	OnHealthChanged.Broadcast(Data.NewValue);	}
		);

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxHealthAttribute()).AddLambda(
[this](const FOnAttributeChangeData& Data)
			{	OnMaxHealthChanged.Broadcast(Data.NewValue);	}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	AuraAttributeSet->GetManaAttribute()).AddLambda(
[this](const FOnAttributeChangeData& Data)
		{	OnManaChanged.Broadcast(Data.NewValue);	}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	AuraAttributeSet->GetMaxManaAttribute()).AddLambda(
[this](const FOnAttributeChangeData& Data)
		{	OnMaxManaChanged.Broadcast(Data.NewValue);	}
	);
	

	// bind a lambda function to the EffectAssetTags delegate on the ability system component
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		// this is the signature for a lamba function (which is an anonymous function). square brackets are for member variables/functions.
		// otherwise it might not know it exists. that is why we have 'this' in the square brackets
		[this](const FGameplayTagContainer& AssetTags)
		{
			// broadcast to our gameplay controller for all of the tags in the gameplay controller
			for (const FGameplayTag& Tag : AssetTags)
			{
				/* For example, say that Tag = Message.HealthPotion. "Message.HealthPotion".MatchesTag("Message") returns true.
				 * "Message".MatchesTag("Message.HealthPotion" will return false. e.g. partial match
				 * In our situation, we just want to check to see if the tag is a message tag specificallty */
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if (Tag.MatchesTag(MessageTag))
				{
				// call our template function to return the widget row, so that we can broadcast it to the widget
				const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
				MessageWidgetRowDelegate.Broadcast(*Row);
				}
			}
		}
	);
}

