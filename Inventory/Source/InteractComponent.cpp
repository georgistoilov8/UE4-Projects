// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "PickableItem.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Misc/OutputDeviceNull.h"
#include "InventoryWidget.h"
#include "Inventory.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UInteractComponent::UInteractComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	
}

// Called when the game starts
void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	if (WidgetInventory) {
		// Create the widget and store it.
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (!IsValid(PlayerController)) {
			UE_LOG(LogTemp, Warning, TEXT("Fail in UInteractComponent::BeginPlay, PlayerController is null"));
			return;
		}
		InventoryMenu = CreateWidget<UUserWidget>(PlayerController, WidgetInventory);

		if (InventoryMenu) {
			InventoryMenu->AddToViewport();
		}
	}

}


// Called every frame
void UInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

/** Interact with one object around the player */
void UInteractComponent::WithAllAround(FVector Position) {
	TArray<class AActor*> ActorsInArea;
	UWorld* World = GetWorld();
	if (!IsValid(World)) {
		UE_LOG(LogTemp, Warning, TEXT("Fail in UInteractComponent::WithAllAround, World == nullptr"));
		return;
	}
	TArray<AActor *> ActorsToIgnore;
	bool IsValidOverlap = UKismetSystemLibrary::SphereOverlapActors(World, Position, SphereRadius, ObjectTypes, nullptr, ActorsToIgnore, ActorsInArea);
	if (IsValidOverlap == true) {
		TArray<APickableItem*> ItemsToPick;
		for (auto actor : ActorsInArea) {
			APickableItem* Item = Cast<APickableItem>(actor);
			if (IsValid(Item) && Item->GetCanInteract() == true) {
				ItemsToPick.Add(Item);
			}
		}
		if (ItemsToPick.Num() > 0) {
			/* Maybe do some more complex choose of what item to pick */
			/* For Example: Pick the item which is closest to player or is in front of the player*/
			int MinimalDistance = SphereRadius * SphereRadius * 100;
			int ItemsIndex = 0;
			int Counter = 0;
			for (auto Item : ItemsToPick) {
				FVector ItemsLocation = Item->GetActorLocation();
				int Distance = (ItemsLocation.X - Position.X)*(ItemsLocation.X - Position.X) +
					(ItemsLocation.Y - Position.Y)*(ItemsLocation.Y - Position.Y) +
					(ItemsLocation.Z - Position.Z)*(ItemsLocation.Z - Position.Z);
				if (Distance < MinimalDistance) {
					MinimalDistance = Distance;
					ItemsIndex = Counter;
				}
				Counter++;
			}
			bool WasPicked = ItemsToPick[ItemsIndex]->PickUp();
			if (WasPicked == true) {
				// If an item is picked then Refresh Inventory
				InventoryWidget->RefreshInventory(InventoryMenu);
			}
			else {
				/*UWorld* World = GetWorld();
				if (!IsValid(World)) {
					UE_LOG(LogTemp, Warning, TEXT("Fail in APickableItem::WithAllAround. World is nullptr"));
					return;
				}*/

				ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(World, 0);
				if (!IsValid(PlayerCharacter)) {
					UE_LOG(LogTemp, Warning, TEXT("Fail in APickableItem::WithAllAround. PlayerCharacter is nullptr"));
					return;
				}

				UInventory* Inventory = PlayerCharacter->FindComponentByClass<UInventory>();
				if (IsValid(Inventory)) {
					/** If the Inventory is Full then show a message. */
					if (Inventory->IsInventoryFull()) {
						InventoryWidget->ShowInventoryMessage(InventoryMenu);
					}
				}
				else {
					UE_LOG(LogTemp, Warning, TEXT("Fail in APickableItem::WithAllAround. Inventory is nullptr"));
					return;
				}
			}
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("There was nothing to pick"));
		}
	}
}

/** Close or open Widget Inventory */
void UInteractComponent::InteractWithInventory() {
	if (IsInventoryOpen == false) {
		InventoryWidget->OpenInventory(InventoryMenu);
	}
	else {
		InventoryWidget->CloseInventory(InventoryMenu);
	}
	IsInventoryOpen = !IsInventoryOpen;
}

/** Drop element */
bool UInteractComponent::DropElementFromInventory(int32 Index) {
	UWorld* World = GetWorld();
	if (!IsValid(World)) {
		UE_LOG(LogTemp, Warning, TEXT("Fail in APickableItem::Drop. World is nullptr"));
		return false;
	}

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(World, 0);
	if (!IsValid(PlayerCharacter)) {
		UE_LOG(LogTemp, Warning, TEXT("Fail in APickableItem::Drop. PlayerCharacter is nullptr"));
		return false;
	}

	AActor* RemovedObject = nullptr;

	UInventory* Inventory = PlayerCharacter->FindComponentByClass<UInventory>();
	if (IsValid(Inventory)) {
		RemovedObject = Inventory->RemoveItem(Index);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Fail in APickableItem::Drop. Inventory is nullptr"));
		return false;
	}

	if (RemovedObject) {
		APickableItem* Item = Cast<class APickableItem>(RemovedObject);
		if (Item) {
			Item->Drop();
		}
		return true;
	}
	return false;
}

/* Attempt to do blueprint in C++, did not work
void UInteractComponent::OpenInventory() {
	EnableMouse();
	if (InventoryMenu)
	{
		//let add it to the view port
		UE_LOG(LogTemp, Warning, TEXT("Open Inventory"));
		InventoryMenu->AddToViewport();
		
	}
}

void UInteractComponent::CloseInventory() {
	DisableMouse();
	if (InventoryMenu)
	{
		//let add it to the view port
		//InventoryMenu->AddToViewport();
		UE_LOG(LogTemp, Warning, TEXT("Close Inventory"));
		InventoryMenu->RemoveFromParent();
	}
}

void UInteractComponent::EnableMouse() {
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (!IsValid(PlayerController)) {
		UE_LOG(LogTemp, Warning, TEXT("Fail in UInteractComponent::DisableMouse, PlayerController is null"));
		return;
	}
	//PlayerController->SetInputMode(FInputModeGameAndUI());
	UWidgetBlueprintLibrary::SetInputMode_GameAndUI(PlayerController, InventoryMenu, true, true);
	
	//AHUD* PlayerControllerHUD = PlayerController->GetHUD();
	//PlayerController->SetInputMode(FInputModeUIOnly());
	PlayerController->bShowMouseCursor = true;
	PlayerController->SetIgnoreLookInput(true);
}

void UInteractComponent::DisableMouse() {
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (!IsValid(PlayerController)) {
		UE_LOG(LogTemp, Warning, TEXT("Fail in UInteractComponent::DisableMouse, PlayerController is null"));
		return;
	}
	
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
	PlayerController->bShowMouseCursor = false;
	PlayerController->SetIgnoreLookInput(false);
}
*/