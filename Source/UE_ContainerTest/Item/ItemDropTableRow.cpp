// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDropTableRow.h"

UClass* FItemDropTableRow::GetItemActor() const
{
    if (item.IsValid() == true)
    {
        UClass* reference = item.LoadSynchronous();
        return reference;
    }
    return nullptr;
}
