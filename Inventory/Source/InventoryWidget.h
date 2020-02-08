// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNARPG_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
		
public:
	/** Helps the communication between the C++ classes and a Widget. All these functions are implemented in Blueprint */

	UFUNCTION(BlueprintImplementableEvent)
		void OpenInventory(UUserWidget* Widget);

	UFUNCTION(BlueprintImplementableEvent)
		void CloseInventory(UUserWidget* Widget);

	UFUNCTION(BlueprintImplementableEvent)
		void RefreshInventory(UUserWidget* Widget);

	UFUNCTION(BlueprintImplementableEvent)
		void ShowInventoryMessage(UUserWidget* Widget);
};
