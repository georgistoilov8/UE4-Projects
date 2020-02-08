// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNARPG_API UInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void WithAllAround(FVector Position);

	UFUNCTION()
	void InteractWithInventory();

	UFUNCTION(BlueprintCallable)
	bool DropElementFromInventory(int32 Index);

 protected:
	 /** Radius of the sphere which overlaps with objects around the player */
	UPROPERTY(EditAnywhere, Category = Interaction)
	float SphereRadius = 250;

	/** What type of objects the sphere will overlap with. For example: Static, Dynamic and etc. */
	UPROPERTY(EditAnywhere, Category = Interaction)
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;

	/** Widget of the Inventory */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> WidgetInventory;

	// Variable to hold the widget After Creating it.
	UUserWidget* InventoryMenu;

	/** Widget of the class which will help with the communication between the code and the Widget of the Inventory */
	UPROPERTY(EditAnywhere, Category = "Widgets")
	class UInventoryWidget* InventoryWidget;

	/** Shows if the Widget Inventory is opened */
	UPROPERTY(VisibleAnywhere, Category = Interaction)
	bool IsInventoryOpen = false;
};
