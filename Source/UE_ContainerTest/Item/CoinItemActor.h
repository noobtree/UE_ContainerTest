// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemActor.h"
#include "CoinItemActor.generated.h"

/**
 * 
 */
UCLASS()
class UE_CONTAINERTEST_API ACoinItemActor : public AItemActor
{
	GENERATED_BODY()
	
public:
	ACoinItemActor();

	virtual bool UseItem(AActor* actorWhoUse) override;
};
