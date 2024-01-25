// Copyright 2024 Thomas Ballantyne. All rights reserved.


#include "CustomPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetSystemLibrary.h" 

#include "PlayerInputInterface.h"
#include "InteractionInterface.h"

#define COLLISION_INTERACTION ECC_GameTraceChannel1

void ACustomPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ACustomPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent)) {

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACustomPlayerController::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACustomPlayerController::Look);
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACustomPlayerController::Jump);
		
		//Start Sprint
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ACustomPlayerController::StartSprint);
		
		//Stop Sprint
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ACustomPlayerController::StopSprint);
		
		//Attack1
		EnhancedInputComponent->BindAction(Attack1Action, ETriggerEvent::Triggered, this, &ACustomPlayerController::Attack1);
		
		//Attack2
		EnhancedInputComponent->BindAction(Attack2Action, ETriggerEvent::Triggered, this, &ACustomPlayerController::Attack2);
		
		//Begin Interact
		EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Started, this, &ACustomPlayerController::BeginInteract);
		
		//End Interact
		EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Triggered, this, &ACustomPlayerController::EndInteract);
		
		// Interact Cancelled
		EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Canceled, this, &ACustomPlayerController::InteractCancelled);
		
	}
}

void ACustomPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetLookatActor();
}

void ACustomPlayerController::Move(const FInputActionValue& Value)
{
	APawn* pawn = GetPawn();
	if (UKismetSystemLibrary::DoesImplementInterface(pawn, UPlayerInputInterface::StaticClass())) {				
		IPlayerInputInterface::Execute_Move(pawn, Value);
	}
}

void ACustomPlayerController::Look(const FInputActionValue& Value)
{
	APawn* pawn = GetPawn();
	if (UKismetSystemLibrary::DoesImplementInterface(pawn, UPlayerInputInterface::StaticClass())) {				
		IPlayerInputInterface::Execute_Look(pawn, Value);
	}
}

void ACustomPlayerController::Jump()
{
	APawn* pawn = GetPawn();
	if (UKismetSystemLibrary::DoesImplementInterface(pawn, UPlayerInputInterface::StaticClass())) {				
		IPlayerInputInterface::Execute_Jump(pawn);
	}
}

void ACustomPlayerController::StartSprint()
{
	APawn* pawn = GetPawn();
	if (UKismetSystemLibrary::DoesImplementInterface(pawn, UPlayerInputInterface::StaticClass())) {				
		IPlayerInputInterface::Execute_StartSprint(pawn);
	}
}

void ACustomPlayerController::StopSprint()
{
	APawn* pawn = GetPawn();
	if (UKismetSystemLibrary::DoesImplementInterface(pawn, UPlayerInputInterface::StaticClass())) {				
		IPlayerInputInterface::Execute_StopSprint(pawn);
	}
}

void ACustomPlayerController::Attack1()
{
	APawn* pawn = GetPawn();
	if (UKismetSystemLibrary::DoesImplementInterface(pawn, UPlayerInputInterface::StaticClass())) {				
		IPlayerInputInterface::Execute_Attack1(pawn);
	}
}

void ACustomPlayerController::Attack2()
{
	APawn* pawn = GetPawn();
	if (UKismetSystemLibrary::DoesImplementInterface(pawn, UPlayerInputInterface::StaticClass())) {				
		IPlayerInputInterface::Execute_Attack2(pawn);
	}
}

void ACustomPlayerController::Attack3()
{
	APawn* pawn = GetPawn();
	if (UKismetSystemLibrary::DoesImplementInterface(pawn, UPlayerInputInterface::StaticClass())) {				
		IPlayerInputInterface::Execute_Attack3(pawn);
	}
}

void ACustomPlayerController::BeginInteract()
{
	if (IsValid(lookatActor) && UKismetSystemLibrary::DoesImplementInterface(lookatActor, UInteractionInterface::StaticClass())) {				
		IInteractionInterface::Execute_BeginInteraction(lookatActor);
	}
}

void ACustomPlayerController::EndInteract()
{
	if (IsValid(lookatActor) && UKismetSystemLibrary::DoesImplementInterface(lookatActor, UInteractionInterface::StaticClass())) {				
		IInteractionInterface::Execute_EndInteraction(lookatActor);
	}
}

void ACustomPlayerController::InteractCancelled()
{
	if (IsValid(lookatActor) && UKismetSystemLibrary::DoesImplementInterface(lookatActor, UInteractionInterface::StaticClass())) {				
		IInteractionInterface::Execute_InteractionCancelled(lookatActor);
	}
}

void ACustomPlayerController::GetLookatActor()
{
	FVector loc;
	FRotator rot;
	GetPlayerViewPoint(loc, rot);

	
	FVector startLoc = loc;
	FVector endLoc = loc + (rot.Vector() * 5000.f);
	FHitResult hit;
	
	GetWorld()->LineTraceSingleByChannel(hit, startLoc, endLoc, COLLISION_INTERACTION, FCollisionQueryParams::DefaultQueryParam);

	if (hit.bBlockingHit)
	{
		if (IsValid(hit.GetActor()) && lookatActor == nullptr)
		{
			lookatActor = hit.GetActor();
			
			if (IsValid(lookatActor) && UKismetSystemLibrary::DoesImplementInterface(lookatActor, UInteractionInterface::StaticClass())) {				
				IInteractionInterface::Execute_LookatBegin(lookatActor);
			}
		}

		return;
	}

	if (IsValid(lookatActor))
	{
		
		if (IsValid(lookatActor) && UKismetSystemLibrary::DoesImplementInterface(lookatActor, UInteractionInterface::StaticClass())) {				
			IInteractionInterface::Execute_LookatEnd(lookatActor);
		}

		lookatActor = nullptr;
	}
}
