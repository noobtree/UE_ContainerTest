// Fill out your copyright notice in the Description page of Project Settings.


#include "HealItemActor.h"

AHealItemActor::AHealItemActor() : AItemActor()
{
	itemName = "HealItem";
	essentialTitleName = "Priest";
	healAmount = 50;

	ConstructorHelpers::FObjectFinder<UStaticMesh> itemMeshAsset(TEXT("/Game/Geometries/SM_HealItem"));
	if (itemMeshAsset.Succeeded() == true)
	{
		meshComponent->SetStaticMesh(itemMeshAsset.Object);
	}
}

bool AHealItemActor::UseItem(AActor* actorWhoUse)
{
	// 아이템 사용 조건 확인 및 컨테이너에서 아이템 삭제 진행
	if (Super::UseItem(actorWhoUse) == true)
	{
		FString debugMsg = FString::Printf(TEXT("아이템(%s)을 1개 사용하였습니다."), *itemName.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, debugMsg);
		return true;
	}
	FString debugMsg = FString::Printf(TEXT("아이템(%s)을 사용할 수 없습니다."), *itemName.ToString());
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, debugMsg);
	return false;
}