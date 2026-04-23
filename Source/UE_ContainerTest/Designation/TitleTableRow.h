// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TitleTableRow.generated.h"

/**
 * 칭호를 나타내는 구조체
 */
USTRUCT(Atomic, BlueprintType)
struct UE_CONTAINERTEST_API FTitleTableRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	// 칭호 고유의 GUID
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGuid titleGuid;

	// 칭호의 이름
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName titleName;
};