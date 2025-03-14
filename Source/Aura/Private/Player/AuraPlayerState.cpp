// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerState.h"


AAuraPlayerState::AAuraPlayerState()
{
	// How often the server will try to update clients (want updating fast for GAS)
	SetNetUpdateFrequency(100.f);
}


