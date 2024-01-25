// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PIRATESOFTWAREGJ_API AMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	AMenuGameMode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:


};
