// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AuraGameplayTags.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	// bind our function to the delegate
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);

	// test code to access gameplay tags
	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
	GEngine->AddOnScreenDebugMessage(
		-1,
		10,
		FColor::Orange,
		FString::Printf(TEXT("Tag %s"), *GameplayTags.Attributes_Secondary_Armor.ToString())
		);
	
}

// a callback function that is called whenever a gameplay effect is applied to somethin that has this ASC
void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	// trigger the delegate functions and pass through the tag container (bound in widget controller)
	EffectAssetTags.Broadcast(TagContainer);


}
