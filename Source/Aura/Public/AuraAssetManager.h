// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "AuraAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	// get the projects asset manager (need to set in config file - defaultengine.ini)
	static UAuraAssetManager& Get();

protected:
	// function that occurs VERY early in the loading process
	virtual void StartInitialLoading() override;
};
