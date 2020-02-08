// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObject.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Components/BillboardComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AInteractableObject::AInteractableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/** Add default root component */
	RootBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Root Box Component"));
	RootBoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	RootComponent = RootBoxComponent;

	/** Create static mesh for the object picked from editor */
	ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh of the pickable object"));
	ObjectMesh->SetupAttachment(RootComponent);
	ObjectMesh->SetRelativeLocation(FVector(0, 0, 0));

	/** Create area around the object where the player can interact with the item */
	InteractionArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Pick up area"));
	InteractionArea->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	InteractionArea->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	InteractionArea->SetupAttachment(RootComponent);
	InteractionArea->OnComponentBeginOverlap.AddUniqueDynamic(this, &AInteractableObject::OnOverlapBegin);
	InteractionArea->OnComponentEndOverlap.AddUniqueDynamic(this, &AInteractableObject::OnOverlapEnd);

	InteractionArea->SetRelativeLocation(FVector(0, 0, 0));

	SetupAreaScale();

	/** Create billboard component for the pick up button */
	ButtonBillboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard Component created"));
	ButtonBillboard->SetupAttachment(RootComponent);
	ButtonBillboard->SetHiddenInGame(true, true);

	ButtonBillboard->SetRelativeLocation(FVector(0, 0, 150));
}

// Called when the game starts or when spawned
void AInteractableObject::BeginPlay()
{
	Super::BeginPlay();
	
	SetupAreaScale();
}

// Called every frame
void AInteractableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PreviousMult != Multiplier || PreviousScaleGrowth != ScaleGrowth) {
		SetupAreaScale();
		PreviousMult = Multiplier;
		PreviousScaleGrowth = ScaleGrowth;
	}
}

// Called when Player starts overlap with the interactable area
void AInteractableObject::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	UE_LOG(LogTemp, Warning, TEXT("Overlap Begin"));
	
	/** Show Billboard over the object when the player is near */
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ButtonBillboard->SetHiddenInGame(false, true);
		CanInteract = true;
	}

	//FInputActionKeyMapping PickUp("Pick Up", EKeys::P, 0, 0, 0, 0);
	//GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping( backKey ); // specific to a controller
	//UPlayerInput::AddEngineDefinedActionMapping(PickUp);
}

// Called when Player stops overlap with the pickable area
void AInteractableObject::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	UE_LOG(LogTemp, Warning, TEXT("Overlap End"));
	
	/** Hide Billboard over the object when the player is near */
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ButtonBillboard->SetHiddenInGame(true, true);
		CanInteract = true;
	}
}

void AInteractableObject::InteractWithObject() {
	UE_LOG(LogTemp, Warning, TEXT("Interaction with object"));
}

/** Calculate the area where the player can interact with the object. It's calculated from ScaleGrowth and Multiplier */
void AInteractableObject::SetupAreaScale() {
	FTransform ObjectsTransform = GetTransform();
	FVector ObjectsScale = ObjectsTransform.GetScale3D();
	FVector PickUpAreaScale = FVector((ObjectsScale.X + ScaleGrowth) * Multiplier, (ObjectsScale.Y + ScaleGrowth) * Multiplier, (ObjectsScale.Z + ScaleGrowth) * Multiplier);
	InteractionArea->SetRelativeScale3D(PickUpAreaScale);
}

/** Return if the player can interact with the object */
bool AInteractableObject::GetCanInteract() const {
	return CanInteract;
}