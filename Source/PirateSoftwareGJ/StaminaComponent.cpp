// Fill out your copyright notice in the Description page of Project Settings.


#include "StaminaComponent.h"

#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values for this component's properties
UStaminaComponent::UStaminaComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStaminaComponent::BeginPlay()
{
	Super::BeginPlay();

	// Get character movement component.
	AActor* owner = GetOwner();
	if (IsValid(owner))
	{
		ACharacter* character = static_cast<ACharacter*>(owner);
		characterMovementComp = character->GetCharacterMovement();
		characterMovementComp->MaxWalkSpeed = walkSpeed;
		characterMovementComp->MaxWalkSpeedCrouched = crouchSpeed;

		player = static_cast<APlayerCharacter*>(owner);
	}

	stamina = maxStamina;
}


// Called every frame
void UStaminaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If the character is currently sprinting.
	if (bSprinting)
	{
		// Check if we are out of sprint.
		if (stamina <= 0.f)
		{
			characterMovementComp->MaxWalkSpeed = walkSpeed;
			bSprinting = false;
			GetWorld()->GetTimerManager().SetTimer(delayTH, this, &UStaminaComponent::StartStaminaGain, staminaGainDelay, false);
		}
		else
		{
			stamina -= DeltaTime * staminaDrainRate;
		}
	}

	// If character is standing still, and not as max stamina, recharge stamina.
	if (bCanGainStamina && stamina < maxStamina && (characterMovementComp->Velocity.Length() <= 0.f || bGainStaminaWhileWalking))
	{
		stamina += DeltaTime * staminaGainRate;

		if (stamina > maxStamina)
			stamina = maxStamina;
	}
}

void UStaminaComponent::SetSprinting(bool bIsSprinting)
{
	if (stamina <= 0.f || characterMovementComp->IsCrouching())
		return;

	bSprinting = bIsSprinting;

	if (bSprinting)
	{
		characterMovementComp->MaxWalkSpeed = sprintSpeed;
		GetWorld()->GetTimerManager().ClearTimer(delayTH);
		bCanGainStamina = false;
		/*if (IsValid(GEngine))
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Cannot gain stamina");*/
	}
	else
	{
		characterMovementComp->MaxWalkSpeed = walkSpeed;

		GetWorld()->GetTimerManager().SetTimer(delayTH, this, &UStaminaComponent::StartStaminaGain,staminaGainDelay, false); 
	}
}

void UStaminaComponent::StartStaminaGain()
{
	bCanGainStamina = true;

	/*if (IsValid(GEngine))
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Can gain stamina"); */
}
