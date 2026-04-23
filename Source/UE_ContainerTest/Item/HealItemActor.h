// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemActor.h"
#include "HealItemActor.generated.h"

/**
 * 
 */
UCLASS()
class UE_CONTAINERTEST_API AHealItemActor : public AItemActor
{
	GENERATED_BODY()
	
public:
	AHealItemActor();

	virtual bool UseItem(AActor* actorWhoUse) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Heal Settings")
	float healAmount;
};
