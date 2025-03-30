// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/CombatInterface.h"

// Add default functionality here for any ICombatInterface functions that are not pure virtual.
int32 ICombatInterface::GetPlayerLevel()
{
	// just a default return - each subclass should implement if it wants somethign different
	return 0;
}
