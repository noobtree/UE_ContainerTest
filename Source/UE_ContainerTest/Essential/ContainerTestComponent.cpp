// Fill out your copyright notice in the Description page of Project Settings.


#include "ContainerTestComponent.h"
#include "UE_ContainerTest/Item/ItemDropTableRow.h"
#include "UE_ContainerTest/Designation/TitleTableRow.h"

// Sets default values for this component's properties
UContainerTestComponent::UContainerTestComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UContainerTestComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UContainerTestComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UContainerTestComponent::AddRandomItem()
{
	if (itemDataTable == nullptr)
	{
		return;
	}

	// 데이터 테이블에 등록된 모든 아이템 목록 얻기
	TArray<FItemDropTableRow*> tableRows;
	itemDataTable->GetAllRows<FItemDropTableRow>(TEXT(""), tableRows);

	// 데이터 테이블에 존재하는 행의 개수가 0보다 작거나 같으면 중단.
	if (tableRows.Num() <= 0)
	{
		return;
	}

	// 데이터 테이블에서 무작위 행 선택
	double randValue = FMath::FRandRange(0.0, 1.0);
	for (const auto row : tableRows)
	{
		if (randValue <= row->dropProbability)
		{
			// 행에 등록된 아이템 얻기
			UClass* cls = row->GetItemActor();
			AItemActor* item = GetWorld()->SpawnActor<AItemActor>(cls, FVector::ZeroVector, FRotator::ZeroRotator);

			if (item != nullptr)
			{
				// 컨테이너에 아이템 등록
				FName key = item->GetItemName();

				// 중복 아이템 검사
				int32 index = itemList.IndexOfByKey(key);
				if (itemList.IsValidIndex(index) == false)
				{
					// 중복 아이템이 존재하지 않으면 컨테이너에 추가
					itemList.Add(key);		// 아이템 추가
					itemCountList.Add(1);	// 개수 추가
					itemInfoMap.Add({ key, item });		// 아이템 정보 추가

					// 테스트 용도 액터의 위치 조정
					item->AddActorLocalOffset(FVector(0, 100 * itemList.Num(), 0));
				}
				else
				{
					// 개수 증가
					itemCountList[index]++;
					// 중복된 종류의 액터 제거
					item->Destroy();
				}

				// 디버그 메시지 출력
				FString debugMsg = FString::Printf(TEXT("1 Item(%s) was Added in Container[TArray]"), *key.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, debugMsg);
				return;
			}
			else
			{
				// 디버그 메시지 출력
				GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Null Reference Item Error"));
			}
		}
		else
		{
			randValue -= row->dropProbability;
		}
	}
}

void UContainerTestComponent::RemoveRandomItem()
{
	// 보유한 아이템이 없으면 중단
	if (itemList.Num() <= 0)
	{
		return;
	}

	// 무작위 아이템 선택
	int32 randIndex = FMath::RandRange(1, itemList.Num()) - 1;
	FName key = itemList[randIndex];

	// 아이템 삭제
	if (itemCountList[randIndex] <= 1)
	{
		itemList.RemoveAtSwap(randIndex);	// 빠른 동작을 위해서 Swap 방식 사용
		itemCountList.RemoveAtSwap(randIndex);	// 빠른 동작을 위해서 Swap 방식 사용
		itemInfoMap[key]->Destroy();	// World에 생성된 액터 제거
		itemInfoMap.Remove(key);	// 보유 아이템 정보 삭제
	}
	else
	{
		// 보유 개수 감소
		itemCountList[randIndex] -= 1;
	}
	return;
}

void UContainerTestComponent::AddSpecifiedItem(const FName& itemName)
{
	// 아이템 데이터 테이블 검색 설정
	FDataTableRowHandle rowHandler;
	rowHandler.DataTable = itemDataTable;
	rowHandler.RowName = itemName;

	// 데이터 테이블에 존재하는 아이템인지 확인
	if (FItemDropTableRow* row = rowHandler.GetRow<FItemDropTableRow>(TEXT("")))
	{
		UClass* cls = row->GetItemActor();
		AItemActor* item = GetWorld()->SpawnActor<AItemActor>(cls, FVector::ZeroVector, FRotator::ZeroRotator);

		// 중복 아이템 검사
		int32 index = itemList.IndexOfByKey(itemName);
		if (itemList.IsValidIndex(index) == false)
		{
			// 중복 아이템이 존재하지 않으면 컨테이너에 추가
			itemList.Add(itemName);		// 아이템 추가
			itemCountList.Add(1);	// 개수 추가
			itemInfoMap.Add({ itemName, item });		// 아이템 정보 추가
		}
		else
		{
			// 개수 증가
			itemCountList[index]++;
			item->Destroy();
		}

		// 디버그 메시지 출력
		FString debugMsg = FString::Printf(TEXT("1 Item(%s) was Added in Container[TArray]"), *itemName.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT(""));
	}
}

void UContainerTestComponent::RemoveSpecifiedItem(const FName& itemName)
{
	// 인덱스 구하기
	int32 index = itemList.IndexOfByKey(itemName);
	
	if (itemList.IsValidIndex(index) == false)
	{
		return;
	}

	// 아이템 삭제
	if (itemCountList[index] <= 1)
	{
		itemList.RemoveAtSwap(index);	// 빠른 동작을 위해서 Swap 방식 사용
		itemCountList.RemoveAtSwap(index);	// 빠른 동작을 위해서 Swap 방식 사용
		itemInfoMap[itemName]->Destroy();	// World에 생성된 액터 제거
		itemInfoMap.Remove(itemName);	// 보유 아이템 정보 삭제
	}
	else
	{
		// 보유 개수 감소
		itemCountList[index] -= 1;
	}
}

void UContainerTestComponent::AddOnScreenDebugMessage_Title() const
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("---------------------------------------------"));
	for (const FName& titleName : titleListInPossessionOf)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, titleName.ToString());
	}
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("-------------보유 칭호 목록------------------"));
}

void UContainerTestComponent::AddOnScreenDebugMessage_Item() const
{
	check(GEngine != nullptr);

	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("---------------------------------------------"));
	// 역순으로 아이템 정보 출력
	for (int32 i = itemList.Num() - 1; i >= 0; --i)
	{
		FName key = itemList[i];

		FString debugMsg = FString::Printf(TEXT("%d. %s %d개"), i, *key.ToString(), itemCountList[i]);
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, debugMsg);
	}
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("-----------보유 아이템 목록--------------------"));
}

bool UContainerTestComponent::CheckActorHasTitle(const FName& titleName)
{
	if (titleName.IsNone() == true)
	{
		return true;
	}
	return titleListInPossessionOf.Contains(titleName);
}

bool UContainerTestComponent::GetEssentialTitleForItem(const FName& itemName)
{
	if (itemInfoMap.Contains(itemName) == true)
	{
		FName titleName = itemInfoMap[itemName]->GetEssentialTitleName();
		if (titleListInPossessionOf.Contains(titleName) == false)
		{
			// 칭호 추가
			titleListInPossessionOf.Add(titleName);

			FString debugMsg = FString::Printf(TEXT("칭호 획득 : [%s]"), *titleName.ToString());
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, debugMsg);
			return true;
		}

		FString debugMsg = FString::Printf(TEXT("중복된 칭호 습득 시도 : [%s]"), *titleName.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Orange, debugMsg);
	}
	return false;
}
