// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicItemActor.h"

AMagicItemActor::AMagicItemActor() : AItemActor()
{
	itemName = "MagicItem";
	essentialTitleName = "Magician";
	ConstructorHelpers::FObjectFinder<UStaticMesh> itemMeshAsset(TEXT("/Game/Geometries/SM_MagicItem"));
	if (itemMeshAsset.Succeeded() == true)
	{
		meshComponent->SetStaticMesh(itemMeshAsset.Object);
	}
}

bool AMagicItemActor::UseItem(AActor* actorWhoUse)
{
	// 아이템 사용 조건 확인 및 컨테이너에서 아이템 삭제 진행
	if (Super::UseItem(actorWhoUse) == true)
	{
		// 액터 순간이동
		actorWhoUse->TeleportTo(FVector(0, 0, 100), FRotator::ZeroRotator);

		FString debugMsg = FString::Printf(TEXT("아이템(%s)을 1개 사용하였습니다."), *itemName.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, debugMsg);
		return true;
	}
	FString debugMsg = FString::Printf(TEXT("아이템(%s)을 사용할 수 없습니다."), *itemName.ToString());
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, debugMsg);
	return false;
}
