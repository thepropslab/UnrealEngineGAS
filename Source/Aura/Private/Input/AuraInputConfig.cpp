// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/AuraInputConfig.h"

// return a given input action for a given tag
const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag,
	bool bLogNotFound) const
{
	for (const FAuraInputAction& Action : AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}

		if (bLogNotFound)
		{
			UE_LOG(LogTemp, Error, TEXT("Can't find ability input action for InputTag [%s], on InputConfig [%s]"), *InputTag.ToString(), *GetNameSafe(this));	
		}
	}
	return nullptr;
}
