# UE4-Project

Project for course Game Engine Architecture in Faculty of Mathematics and Informatics.

Link to zip of the project: https://drive.google.com/open?id=1ZoOSueqFr6buskekoSXBSEkAWcWqMVrk

Това се добавя в YourPlayerController.cpp
```c++
#include "../Inventory/InteractComponent.h"
#include "Kismet/GameplayStatics.h"
...
void ATopDownARPGPlayerController::PickUpItem() {
	UWorld* World = GetWorld();
	if (!IsValid(World)) {
		UE_LOG(LogTemp, Warning, TEXT("Fail in ATopDownARPGPlayerController::PickUpItem. World is nullptr"));
		return;
	}
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(World, 0);
	if (!IsValid(PlayerCharacter)) {
		UE_LOG(LogTemp, Warning, TEXT("Fail in ATopDownARPGPlayerController::PickUpItem. PlayerCharacter is nullptr"));
		return;
	}
	UInteractComponent* Interact = PlayerCharacter->FindComponentByClass<UInteractComponent>();
	if (IsValid(Interact)) {
		APawn* CharacterPawn = this->GetPawn();
		if (IsValid(CharacterPawn)) {
			FVector CharacterPosition = CharacterPawn->GetActorLocation();
			Interact->WithAllAround(CharacterPosition);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Fail in ATopDownARPGPlayerController::PickUpItem. CharacterPawn is nullptr"));
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Fail in ATopDownARPGPlayerController::PickUpItem. Interact is nullptr"));
	}
}

void ATopDownARPGPlayerController::UseInventory() {
	UWorld* World = GetWorld();
	if (!IsValid(World)) {
		UE_LOG(LogTemp, Warning, TEXT("Fail in ATopDownARPGPlayerController::UseInventory. World is nullptr"));
		return;
	}
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(World, 0);
	if (!IsValid(PlayerCharacter)) {
		UE_LOG(LogTemp, Warning, TEXT("Fail in ATopDownARPGPlayerController::UseInventory. PlayerCharacter is nullptr"));
		return;
	}
	UInteractComponent* Interact = PlayerCharacter->FindComponentByClass<UInteractComponent>();
	if (IsValid(Interact)) {
		Interact->InteractWithInventory();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Fail in ATopDownARPGPlayerController::UseInventory. Interact is nullptr"));
	}
}
```
YourPlayerController.h
```c++
void PickUpItem();
void UseInventory();
```
