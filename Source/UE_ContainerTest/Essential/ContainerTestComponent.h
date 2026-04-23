// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UE_ContainerTest/Item/ItemActor.h"
#include "ContainerTestComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE_CONTAINERTEST_API UContainerTestComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UContainerTestComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


protected:
	// 보유한 칭호의 고유 키 목록
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General|Title Settings")
	TSet<FName> titleListInPossessionOf;

	// 보유한 아이템의 고유 키들을 관리하는 컨테이너
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General|Inventory Settings")
	TArray<FName> itemList;

	// 보유한 아이템의 개수를 저장하는 컨테이너
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General|Inventory Settings")
	TArray<int32> itemCountList;

	// (테스트 용도) 인벤토리에 아이템 추가 시 아이템 추가 확률을 정의한 데이터 테이블
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (RequiredAssetDataTags = "RowStructure=/Script/UE_ContainerTest.ItemDropTableRow"), Category = "General|Item Settings")
	TObjectPtr<UDataTable> itemDataTable;

	// 보유한 아이템의 정보를 아이템 데이터 테이블에서 꺼내와서 저장하는 컨테이너
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General|Item Settings")
	TMap<FName, AItemActor*> itemInfoMap;

public:
	// 무작위 아이템을 컨테이너에 추가
	UFUNCTION(BlueprintCallable, Category = "Test|Functions")
	void AddRandomItem();

	// 보유한 목록 중 무작위 아이템을 컨테이너에서 제거
	UFUNCTION(BlueprintCallable, Category = "Test|Functions")
	void RemoveRandomItem();

	// 특정 아이템 1개를 컨테이너에 추가
	UFUNCTION(BlueprintCallable, Category = "Test|Functions")
	void AddSpecifiedItem(const FName& itemName);

	// 보유하고 있는 특정 아이템을 1개 제거하는 함수
	UFUNCTION(BlueprintCallable, Category = "Test|Functions")
	void RemoveSpecifiedItem(const FName& itemName);

	// 컨테이너에 보관중인 칭호 목록을 디버그 메시지로 출력
	UFUNCTION(BlueprintCallable, Category = "Test|Functions")
	void AddOnScreenDebugMessage_Title() const;

	// 컨테이너에 보관중인 아이템 목록을 디버그 메시지로 출력
	UFUNCTION(BlueprintCallable, Category = "Test|Functions")
	void AddOnScreenDebugMessage_Item() const;

	// 컨테이너에 보유한 칭오가 존재하는지 확인하는 함수
	UFUNCTION(BlueprintCallable, Category = "Test|Functions")
	bool CheckActorHasTitle(const FName& titleName);

	// 컨테이너에 보유한 칭오가 존재하는지 확인하는 함수
	UFUNCTION(BlueprintCallable, Category = "Test|Functions")
	bool GetEssentialTitleForItem(const FName& itemName);
};
