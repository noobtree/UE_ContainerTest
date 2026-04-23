// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemActor.h"
#include "MagicItemActor.generated.h"

/**
 * 
 */
UCLASS()
class UE_CONTAINERTEST_API AMagicItemActor : public AItemActor
{
	GENERATED_BODY()
public:
	AMagicItemActor();

	virtual bool UseItem(AActor* actorWhoUse) override;
};
