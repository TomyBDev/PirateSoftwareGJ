// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StaminaComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PIRATESOFTWAREGJ_API UStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStaminaComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetStamina() const { return stamina; }

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetMaxStamina() const { return maxStamina; }

	void SetSprinting(bool bIsSprinting);

private:

	void StartStaminaGain();

	/** Sprint Variable */
	UPROPERTY(EditAnywhere, Category = "Sprint")
	float walkSpeed = 240.f;

	UPROPERTY(EditAnywhere, Category = "Sprint")
	float sprintSpeed = 540.f;

	UPROPERTY(EditAnywhere, Category = "Sprint")
	float crouchSpeed = 120.f;

	UPROPERTY(EditAnywhere, Category = "Sprint", BlueprintGetter = GetMaxStamina)
	float maxStamina = 5.f;

	UPROPERTY(EditAnywhere, Category = "Sprint")
	float staminaDrainRate = 1.f;

	UPROPERTY(EditAnywhere, Category = "Sprint")
	float staminaGainRate = 1.f;

	UPROPERTY(BlueprintGetter = GetStamina)
	float stamina;

	bool bSprinting = false;

	bool bCanGainStamina = false;

	UPROPERTY(EditAnywhere, Category = "Sprint")
	bool bGainStaminaWhileWalking = false;
		
	/** Character Component */
	class UCharacterMovementComponent* characterMovementComp;

	class APlayerCharacter* player;

	/** Timer */
	FTimerHandle delayTH;

	UPROPERTY(EditAnywhere, Category = "Sprint")
	float staminaGainDelay = 1.5f;
};
