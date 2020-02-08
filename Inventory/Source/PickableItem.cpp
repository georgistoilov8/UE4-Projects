// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableItem.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Inventory.h"
#include "GameFramework/Character.h"
#include "Engine/Texture2D.h"

/** Pick object */
void APickableItem::InteractWithObject() {
	Super::InteractWithObject();
	
	bool IsItemAdded = false;

	UWorld* World = GetWorld();
	if (!IsValid(World)) {
		UE_LOG(LogTemp, Warning, TEXT("Fail in APickableItem::InteractWithObject. World is nullptr"));
		return;
	}
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(World, 0);
	if (!IsValid(PlayerCharacter)) {
		UE_LOG(LogTemp, Warning, TEXT("Fail in APickableItem::InteractWithObject. PlayerCharacter is nullptr"));
		return;
	}
	UInventory* Inventory = PlayerCharacter->FindComponentByClass<UInventory>();
	if (IsValid(Inventory)) {
		IsItemAdded = Inventory->AddItem(this);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Fail in APickableItem::InteractWithObject. Inventory is nullptr"));
		return;
	}

	if (IsItemAdded == true) {
		//Destroy();
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		SetWasObjectPicked(true);
	}
}

/** Public function which calls InteractWithObject() */
bool APickableItem::PickUp() {
	InteractWithObject();
	return GetWasObjectPicked();
}

/** Drop Object. Actually move it in front of the player and set it visible again*/
bool APickableItem::Drop() {
	UWorld* World = GetWorld();
	if (!IsValid(World)) {
		UE_LOG(LogTemp, Warning, TEXT("Fail in APickableItem::Drop. World is nullptr"));
		return false;
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
	if (!IsValid(PlayerController)) {
		UE_LOG(LogTemp, Warning, TEXT("Fail in APickableItem::Drop. PlayerController is nullptr"));
		return false;
	}

	APawn* PlayerPawn = PlayerController->GetPawn();
	if (!IsValid(PlayerPawn)) {
		UE_LOG(LogTemp, Warning, TEXT("Fail in APickableItem::Drop. PlayerPawn is nullptr"));
		return false;
	}

	FVector PlayerLocation = PlayerPawn->GetActorLocation();
	FVector ForwardDirection = PlayerPawn->GetActorForwardVector();

	FVector SpawnLocation = PlayerLocation + ForwardDirection * 100.0f;

	SetActorLocation(SpawnLocation, false, 0, ETeleportType::None);

	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetWasObjectPicked(false);
	return true;

}
