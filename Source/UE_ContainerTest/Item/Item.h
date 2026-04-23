// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Item.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UItem : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UE_CONTAINERTEST_API IItem
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// 아이템의 이름을 얻는 함수
	virtual FName GetItemName() const = 0;

	// 아이템 아이콘의 텍스쳐 에셋을 얻는 함수
	virtual UTexture2D* GetItemIconTexture() const = 0;

	// 아이템을 사용하기 위한 칭호 정보를 얻는 함수
	virtual FName GetEssentialTitleName() const = 0;

	virtual bool UseItem(AActor* actorWhoUse) = 0;
};
