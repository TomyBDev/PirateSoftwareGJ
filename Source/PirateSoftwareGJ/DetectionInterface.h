// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.

#pragma once

#include "DetectionInterface.generated.h"

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
	void StartDetection();
	virtual void StartDetection_Implementation() {}

	/** End Detection */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
	void EndDetection();
	virtual void EndDetection_Implementation() {}
	
};