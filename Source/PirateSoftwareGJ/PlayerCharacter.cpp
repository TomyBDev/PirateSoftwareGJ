// Copyright 2024 Thomas Ballantyne. All rights reserved.


#include "PlayerCharacter.h"

#include "CustomGameInstance.h"
#include "EnhancedInputSubsystems.h"
#include "StaminaComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = true;

	
	GetCapsuleComponent()->InitCapsuleSize(38.f,12.f);
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;

	sprintArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Sprint Arm Component"));
	sprintArm->SetupAttachment(RootComponent);
	sprintArm->TargetArmLength = 400.0f; // The camera follows at this distance behind the character
	sprintArm->SocketOffset = FVector(0.0f, 0.f, 550.f);
	sprintArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	sprintArm->ProbeSize = 16.f;
	sprintArm->bEnableCameraLag = true;
	sprintArm->CameraLagSpeed = 16;
	
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	camera->SetupAttachment(sprintArm, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	camera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	camera->SetRelativeRotation(FRotator(0.f, -50.f, 0.f));

	cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cubez"));
	cube->SetupAttachment(RootComponent);

	/** Initilaise Stamina Component. */
	staminaComp = CreateDefaultSubobject<UStaminaComponent>(TEXT("Stamina Component"));
	AddOwnedComponent(staminaComp);

	Tags.Add("Player");
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	UCustomGameInstance* cgi = Cast<UCustomGameInstance>(GetGameInstance());
	if(IsValid(cgi))
		sensitivity = cgi->GetGeneralSettings().sensitivity / 5.f;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Hypothetically if the player needs some super specific input, we could put it here.

}

void APlayerCharacter::Move_Implementation(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlayerCharacter::Look_Implementation(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (!IsValid(Controller))
		return;

	// add yaw and pitch input to controller
	AddControllerPitchInput(LookAxisVector.Y * sensitivity);
	AddControllerYawInput(LookAxisVector.X * sensitivity);

	FRotator rot = GetController()->GetControlRotation();;
	GetController()->SetControlRotation(FRotator(FMath::ClampAngle(FMath::UnwindDegrees(rot.Pitch), -30.f, 30.f), rot.Yaw, rot.Roll));
	
}

void APlayerCharacter::Jump_Implementation()
{
	//Super::Jump();
}

void APlayerCharacter::StartSprint_Implementation()
{
	staminaComp->SetSprinting(true);
}

void APlayerCharacter::StopSprint_Implementation()
{
	staminaComp->SetSprinting(false);
}

void APlayerCharacter::Attack1_Implementation()
{
	if (!bCloaked)
	{
		cube->SetMaterial(0, translucentMat);
		Tags.RemoveAt(0);
		bCloaked = true;
		//ToDo: Fix AI detection of player round cloaking.
		GetWorld()->GetTimerManager().SetTimer(cloakTH, this, &APlayerCharacter::EndCloak, cloakTime, false);
	}

}

void APlayerCharacter::Attack2_Implementation()
{
	Ability2();
}

void APlayerCharacter::Attack3_Implementation()
{
	
}

void APlayerCharacter::Interact_Implementation()
{
	
}

void APlayerCharacter::EndCloak()
{
	//ToDo: Fix AI detection of player round cloaking.
	cube->SetMaterial(0, normalMat);
	Tags.Add("Player");
	bCloaked = false;
}
