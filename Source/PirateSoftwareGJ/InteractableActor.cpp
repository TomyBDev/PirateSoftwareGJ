// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.


#include "InteractableActor.h"

#include "InteractWidget.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
AInteractableActor::AInteractableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	RootComponent = rootComp;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	mesh->SetupAttachment(rootComp);

	interactionCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Collider"));
	interactionCollider->SetupAttachment(rootComp);
	interactionCollider->SetCollisionResponseToChannel(COLLISION_INTERACTION, ECR_Block);

	interactWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interact Widget"));
	interactWidget->SetupAttachment(mesh);

	static ConstructorHelpers::FClassFinder <UUserWidget> widgetClass(TEXT("/Script/UMG.WidgetBlueprintGeneratedClass'/Game/Widgets/Interaction/WBP_Interact.WBP_Interact_C'"));
	interactWidget->SetWidgetClass(widgetClass.Class);
	interactWidget->SetDrawSize(FVector2d(240.f, 240.f));
}

// Called when the game starts or when spawned
void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();

	// Set Interaction Widget Hidden in game.
	interactionWidget = Cast<UInteractWidget>(interactWidget->GetWidget());
	if (IsValid(interactionWidget))
		interactWidget->SetHiddenInGame(true);
	
}

// Called every frame
void AInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AInteractableActor::BeginInteraction_Implementation()
{
	if (bLockInteraction)
		return true;
	
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, TEXT("Begin Interaction!"));
	
	GetWorld()->GetTimerManager().SetTimer(incrementTH, this, &AInteractableActor::IncrementPercent, 0.01f, true);

	return false;
}

bool AInteractableActor::EndInteraction_Implementation()
{
	if (bLockInteraction || (IsValid(interactionWidget) && interactionWidget->GetPercentage() < 1.0f))
		return true;
	
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, TEXT("End Interaction!"));
	
	bLockInteraction = true;

	GetWorld()->GetTimerManager().ClearTimer(incrementTH);

	return false;
}

bool AInteractableActor::InteractionCancelled_Implementation()
{
	if (bLockInteraction)
		return true;
	
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, TEXT("Interaction Cancelled!"));
	
	interactionWidget->ZeroPercentage();

	GetWorld()->GetTimerManager().ClearTimer(incrementTH);

	return false;
}

bool AInteractableActor::LookatBegin_Implementation()
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, TEXT("Lookat Begin!"));
	
	interactWidget->SetHiddenInGame(false);

	return false;
}

bool AInteractableActor::LookatEnd_Implementation()
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, TEXT("Lookat End!"));
	
	interactWidget->SetHiddenInGame(true);

	return false;
}

void AInteractableActor::IncrementPercent()
{
	if (IsValid(interactionWidget))
		interactionWidget->IncrementPercentage(0.01f);
}

