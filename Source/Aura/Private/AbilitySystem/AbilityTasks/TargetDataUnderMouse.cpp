// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	// template function to create the ability task and return it
	UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	return MyObj;
}

void UTargetDataUnderMouse::Activate()
{
	// get the data and broadcast the delegate with valid data. ability tasks have an owning ability and thus controller
	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	if (PC)
		{
		FHitResult CursorHit;
		PC->GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
		ValidData.Broadcast(CursorHit.Location);
		}

}
