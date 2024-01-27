// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PIRATESOFTWAREGJ_API AMainGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	AMainGameModeBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void PlayerDied();
	void PlayerWon();

private:

	void DeathTimerComplete();

	FTimerHandle deathScreenTH;

	float deathScreenTime = 5.f;
};
