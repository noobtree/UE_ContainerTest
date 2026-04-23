// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinItemActor.h"

ACoinItemActor::ACoinItemActor() : AItemActor()
{
	itemName = "CoinItem";

	ConstructorHelpers::FObjectFinder<UStaticMesh> itemMeshAsset(TEXT("/Game/Geometries/SM_CoinItem"));
	if (itemMeshAsset.Succeeded() == true)
	{
		meshComponent->SetStaticMesh(itemMeshAsset.Object);
	}
}

bool ACoinItemActor::UseItem(AActor* actorWhoUse)
{
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
