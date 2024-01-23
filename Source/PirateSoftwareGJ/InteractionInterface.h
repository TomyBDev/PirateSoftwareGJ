#pragma once

#include "InteractionInterface.generated.h"

UINTERFACE(MinimalAPI)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

class PIRATESOFTWAREGJ_API IInteractionInterface
{
	GENERATED_BODY()

public:

	/** Begin Interaction */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
	void BeginInteraction();
	virtual void BeginInteraction_Implementation() {};

	/** End Interaction */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
	void EndInteraction();
	virtual void EndInteraction_Implementation() {};

	/** Interaction Cancelled */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
	void InteractionCancelled();
	virtual void InteractionCancelled_Implementation() {};

	/** Lookat Begin */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
	void LookatBegin();
	virtual void LookatBegin_Implementation() {};

	/** Lookat End */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
	void LookatEnd();
	virtual void LookatEnd_Implementation() {};
};