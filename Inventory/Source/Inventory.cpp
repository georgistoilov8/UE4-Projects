// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "ItemsDatabase.h"
#include "PickableItem.h"
#include "Engine/UserDefinedStruct.h"

// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

/** Add item to Inventory */
bool UInventory::AddItem(APickableItem* item) {
	if (Items.Num() + 1 > InitialCapacity) {
		return false;
	}
	Items.Add(item);
	return true;
}

/** Remove item from Inventory*/
AActor* UInventory::RemoveItem(int32 Index) {
	if (Index < 0 || Index >= Items.Num()) {
		return nullptr;
	}
	AActor* ItemToBeRemoved = Items[Index];
	Items.RemoveAt(Index);
	
	return ItemToBeRemoved;
}

/** Shows if the Inventory is Full */
bool UInventory::IsInventoryFull() {
	return InitialCapacity == Items.Num();
}

