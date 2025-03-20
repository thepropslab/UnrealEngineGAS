// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AuraEffectActor.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

AAuraEffectActor::AAuraEffectActor()
{

	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot")));
}


void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

// Apply the gameplay effect to the ability system of an actor
void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	// handy way of getting the ability system component with static function library
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr) return;
	
	check(GameplayEffectClass);
	// create a handle which is a wrapper for some an effect context. has internal data member.
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	// store the object that caused the effect (in the effect context)
	EffectContextHandle.AddSourceObject(this);
	// sometimes called effect spec. the wrapper for the effect spec. have internal data member.
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);

	// dereference the gameplayeffectspec const reference for the function
	TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	
}


