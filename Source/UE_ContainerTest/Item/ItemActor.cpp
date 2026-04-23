// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemActor.h"
#include "UE_ContainerTest/Essential/ContainerTestComponent.h"

// Sets default values
AItemActor::AItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sceneRoot = CreateDefaultSubobject<USceneComponent>(FName("DefaultSceneComponent"));
	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMeshComponent"));

	SetRootComponent(sceneRoot);
	meshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemActor::UpdateStaticMesh()
{
	return;
}

FName AItemActor::GetItemName() const
{
	return itemName;
}

UTexture2D* AItemActor::GetItemIconTexture() const
{
	if (itemIconTexture != nullptr)
	{
		return itemIconTexture;
	}
	return nullptr;
}

FName AItemActor::GetEssentialTitleName() const
{
	return essentialTitleName;
}

bool AItemActor::UseItem(AActor* actorWhoUse)
{
	// 액터에게 특정 컴포넌트가 존재하는지 확인
	if (UContainerTestComponent* component = actorWhoUse->FindComponentByClass<UContainerTestComponent>())
	{
		// 필요한 칭호가 존재하는지 확인
		bool bIsUsable = component->CheckActorHasTitle(essentialTitleName);

		// 필요 조건을 만족한 경우 아이템 1개 삭제
		if (bIsUsable == true)
		{
			component->RemoveSpecifiedItem(itemName);
			return true;
		}
	}
	return false;
}

