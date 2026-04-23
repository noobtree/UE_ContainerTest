// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.h"
#include "ItemActor.generated.h"

UCLASS()
class UE_CONTAINERTEST_API AItemActor : public AActor, public IItem
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AItemActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY()
	TObjectPtr<USceneComponent> sceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UStaticMeshComponent> meshComponent;

	// 아이템 이름
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "General Settings")
	FName itemName;

	// 아이템 Icon 텍스쳐 에셋
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "General Settings")
	TObjectPtr<UTexture2D> itemIconTexture;

	// 아이템을 사용하기 위해 필요한 칭호의 이름
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "General Settings")
	FName essentialTitleName;

public:
	UFUNCTION(BlueprintCallable)
	void UpdateStaticMesh();

	// 아이템의 이름을 얻는 함수
	UFUNCTION(BlueprintCallable)
	virtual FName GetItemName() const override;

	// 아이템 아이콘의 텍스쳐 에셋을 얻는 함수
	UFUNCTION(BlueprintCallable)
	virtual UTexture2D* GetItemIconTexture() const override;

	// 아이템을 사용하기 위한 칭호 정보를 얻는 함수
	UFUNCTION(BlueprintCallable)
	virtual FName GetEssentialTitleName() const override;

	UFUNCTION(BlueprintCallable)
	virtual bool UseItem(AActor* actorWhoUse) override;
};
