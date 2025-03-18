// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

struct FOnAttributeChangeData;
// want dynamic multicast delegates so we can assign events in blueprints
// declaring a delegate that can broadcast health and max health
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);

UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	// Create OnHealthChanged delegate with the delegate type/signature that was passi nto the delegates above
	// these delegates will bound in blueprints. anything that has access to the widget controller can access
	UPROPERTY(BlueprintAssignable, Category = "Gas|Attributes")
	FOnHealthChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category = "Gas|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;

protected:
	// These functions MUST have this signature in order to work with the attirbute change delegate
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
	
};
