// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	// whenever an attribute is changed, we cycle through the tags to see which variable has changed.
	// then use a lambda to broadcast the changes to the dependencies
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	check (AttributeInfo);
	for (auto Pair: AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
		[this, Pair](const FOnAttributeChangeData& Data)
		{
			BroadcastAttributeInfo(Pair.Key, Pair.Value());
		}
		);
	}
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	// get the attribute info class and the attribute set, then use it to broadcast a change to the attribtue
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	check (AttributeInfo);

	// loop through our attribute set key-value pair to assign tags and numbers to each attribute
	// SEE AURA ATTRIBUTE SET.h. only broadcasts the initial values
	for (auto& Pair : AS->TagsToAttributes)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}
	
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const
{
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
