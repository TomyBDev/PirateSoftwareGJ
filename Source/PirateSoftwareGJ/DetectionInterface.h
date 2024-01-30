// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.

#pragma once

#include "DetectionInterface.generated.h"

class APlayerCharacter;

UINTERFACE(MinimalAPI)
class UDetectionInterface : public UInterface
{
	GENERATED_BODY()
};

class PIRATESOFTWAREGJ_API IDetectionInterface
{
	GENERATED_BODY()

public:

	/** Start Detection */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
	void StartDetection(AActor* otherActor);
	virtual void StartDetection_Implementation(AActor* otherActor) {}

	/** End Detection */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
	void EndDetection(AActor* otherActor);
	virtual void EndDetection_Implementation(AActor* otherActor) {}
	
};