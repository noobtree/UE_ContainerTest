// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemActor.h"
#include "ItemDropTableRow.generated.h"

/**
 * 
 */
USTRUCT(Atomic, BlueprintType)
struct UE_CONTAINERTEST_API FItemDropTableRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	// 아이템
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftClassPtr<AItemActor> item;

	// 드롭 확률
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float dropProbability = 0.1f;

public:
	UClass* GetItemActor() const;
};