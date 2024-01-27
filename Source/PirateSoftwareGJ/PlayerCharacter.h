// Copyright 2024 Thomas Ballantyne. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PlayerInputInterface.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class PIRATESOFTWAREGJ_API APlayerCharacter : public ACharacter, public IPlayerInputInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	class UStaminaComponent* GetStaminaComponent() const { return staminaComp; }

	UFUNCTION(BlueprintImplementableEvent)
	void Ability1();

	
	UFUNCTION(BlueprintImplementableEvent)
	void Ability2();

	bool GetIsCloaked() const { return bCloaked; }

protected:
	virtual void Move_Implementation(const FInputActionValue& Value) override;

	virtual void Look_Implementation(const FInputActionValue& Value) override;

	virtual void Jump_Implementation() override;

	virtual void StartSprint_Implementation() override;

	virtual void StopSprint_Implementation() override;
	
	virtual void Attack1_Implementation() override;
	
	virtual void Attack2_Implementation() override;
	
	virtual void Attack3_Implementation() override;

	virtual void Interact_Implementation() override;

private:

	void EndCloak();

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* sprintArm;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	
	class UCameraComponent* camera;
	
	/** Cube */
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* cube;
	
	/** Stamina Component. */
	UPROPERTY(EditAnywhere, Category = "Stamina Component", BlueprintGetter = GetStaminaComponent)
	class UStaminaComponent* staminaComp;

	UPROPERTY(EditAnywhere)
	UMaterial* normalMat;
	
	UPROPERTY(EditAnywhere)
	UMaterial* translucentMat;

	float sensitivity = 1.f;
	
	FTimerHandle cloakTH;

	float cloakTime = 5.f;

	bool bCloaked = false;
};
