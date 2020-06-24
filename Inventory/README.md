# UE4-Project

Project for course Game Engine Architecture in Faculty of Mathematics and Informatics.

Link to zip of the project: https://drive.google.com/open?id=1ZoOSueqFr6buskekoSXBSEkAWcWqMVrk

За реализацията на този проект са създадени обкети, които могат да бъдат взимани от играча. Показани са как изглеждат  
на долната фигура
![alt text](https://github.com/georgistoilov8/UE4-Projects/blob/master/Inventory/inventory_1.png "Inventory_1")

След стартиране на проекта при натискане на бутона "I" се показва инвентара.
![alt text](https://github.com/georgistoilov8/UE4-Projects/blob/master/Inventory/inventory_2.png "Inventory_2")

При преминаване покрай обектите за взимане над тях се показва иконка. Това показва, че този обект може да бъде взет.  
При натискане на бутона "P" обектът се прибира в инвентара. Тогава при показване на инвентара вече имаме и обекти в него.
![alt text](https://github.com/georgistoilov8/UE4-Projects/blob/master/Inventory/inventory_3.png "Inventory_3")

И ако случайно искаме да премахнем обект от инвентара просто кликваме върху него и излизат опции, които могат да се извършат с този обект.
![alt text](https://github.com/georgistoilov8/UE4-Projects/blob/master/Inventory/inventory_4.png "Inventory_4")

Важно!  
За да започне да се показва визуалната част от инвентара е необходимо да се направи следното:  
Отваря се Blueprint-а на TopDownCharacter и се отива на Interaction Component. Там има поле Widgets.  
Widget_Inventory се задава да е Widget_Inventory  
Inventory_Widget се задава да е WidgetInventoryFromClass


Това се добавя в YourPlayerController.cpp
```c++
#include "../Inventory/InteractComponent.h"
#include "Kismet/GameplayStatics.h"
...
void ATopDownARPGPlayerController::SetupInputComponent()
{
	...
	InputComponent->BindAction("PickUp", IE_Pressed, this, &ATopDownARPGPlayerController::PickUpItem);
	InputComponent->BindAction("UseInventory", IE_Pressed, this, &ATopDownARPGPlayerController::UseInventory);
}
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
