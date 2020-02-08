// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNARPG_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	/** Shows the capacity of Inventory */
	UPROPERTY(VisibleAnywhere, Category = Inventory)
	int InitialCapacity = 8;

	/** Array of the elements in Inventory */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
	TArray<APickableItem*> Items;

public:
	UFUNCTION()
	bool AddItem(APickableItem* item);
	
	UFUNCTION(BlueprintCallable)
	AActor* RemoveItem(int32 Index);

	UFUNCTION(BlueprintCallable)
	bool IsInventoryFull();
};
