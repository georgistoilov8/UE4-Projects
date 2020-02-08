// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableObject.generated.h"

UCLASS()
class TOPDOWNARPG_API AInteractableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	float PreviousMult = Multiplier;
	float PreviousScaleGrowth = ScaleGrowth;
	bool CanInteract = false;

	void SetupAreaScale();
protected:
	/** Used to scale the area of interaction */
	UPROPERTY(EditAnywhere, Category = Interaction)
	float Multiplier = 1;

	/** Used to scale the area of interaction */
	UPROPERTY(EditAnywhere, Category = Interaction)
	float ScaleGrowth = 5;
	
	/** The mesh you want to present in the scene */
	UPROPERTY(EditAnywhere, Category = Interaction)
	class UStaticMeshComponent* ObjectMesh;

	/** Area of interaction */
	UPROPERTY(VisibleAnywhere, Category = Interaction)
	class UBoxComponent* InteractionArea;

	/** Default root component */
	UPROPERTY(VisibleAnywhere, Category = Interaction)
	class UBoxComponent* RootBoxComponent;

	/** The texture for which button to press to interact */
	UPROPERTY(VisibleAnywhere, Category = Interaction)
	class UBillboardComponent* ButtonBillboard;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void InteractWithObject();

public:
	UFUNCTION()
	bool GetCanInteract() const;
};
