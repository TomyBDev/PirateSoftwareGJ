// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.


#include "EndLevel.h"

#include "MainGameModeBase.h"
#include "PlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEndLevel::AEndLevel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp")); 
	RootComponent = rootComp;
	
	collisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	collisionBox->SetupAttachment(rootComp);
	collisionBox->SetBoxExtent(FVector(500,500,500));
	collisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	collisionBox->OnComponentBeginOverlap.AddDynamic(this, &AEndLevel::OnOverlapBegin);
	
}

// Called when the game starts or when spawned
void AEndLevel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEndLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEndLevel::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(Cast<APlayerCharacter>(OtherActor)))
	{
		AMainGameModeBase* gm = Cast<AMainGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		if (IsValid(gm))
			gm->PlayerWon();
	}
}

