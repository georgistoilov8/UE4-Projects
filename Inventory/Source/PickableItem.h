// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/InteractableObject.h"
#include "PickableItem.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNARPG_API APickableItem : public AInteractableObject
{
	GENERATED_BODY()
	
private:
	bool WasObjectPicked = false;
public: 
	bool PickUp();

	UFUNCTION()
	bool Drop();

	UFUNCTION()
	void SetWasObjectPicked(bool Value) { WasObjectPicked = Value; }

	UFUNCTION()
	bool GetWasObjectPicked() { return WasObjectPicked; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Pick")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Pick")
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Pick")
	UTexture2D* ItemTexture;
	
	virtual void InteractWithObject() override;
};
