// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"
#include "AbilitySystemComponent.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	// template function to create the ability task and return it
	UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	return MyObj;
}

void UTargetDataUnderMouse::Activate()
{

	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
	if (bIsLocallyControlled)
	{
		SendMouseCursorData();
	}
	else
	{
		//TODO: We are on the server, so listen for target data
	}
	
	// get the data and broadcast the delegate with valid data. ability tasks have an owning ability and thus controller


}

void UTargetDataUnderMouse::SendMouseCursorData()
{
	//create scoped prediction window for our key to use below
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());
	
	// get the hit result from cursor trace, then feed that into our target data to send to server
	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult CursorHit;
	PC->GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	// create a data handle to package up target data
	FGameplayAbilityTargetDataHandle DataHandle;
	
	// create a new object of single target hit data and package it up in the handle
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult = CursorHit;
	DataHandle.Add(Data);
	
	// get the ability system component, and use it to send data to the server
	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		DataHandle,
		 FGameplayTag(),
		AbilitySystemComponent->ScopedPredictionKey);

	// Check if we want to broadcast delegates to clients - checks that ability is still active
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}
