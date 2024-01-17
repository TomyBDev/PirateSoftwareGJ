// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.


#include "EnemyCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	cameraComp->SetupAttachment(RootComponent);
	
	GetCharacterMovement()->MaxWalkSpeed = 300;
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FMinimalViewInfo viewInfo;
	
	cameraComp->GetCameraView(DeltaTime, viewInfo);

	FMatrix viewMatrix, projMatrix;
	
	UGameplayStatics::GetViewProjectionMatrix(viewInfo, viewMatrix, projMatrix, viewProjMatrix);

	viewProjMatrix.DebugPrint();
}

