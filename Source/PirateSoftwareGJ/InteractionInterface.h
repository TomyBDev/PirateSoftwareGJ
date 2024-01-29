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
	bool BeginInteraction();
	virtual bool BeginInteraction_Implementation() { return false; };

	/** End Interaction */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
	bool EndInteraction();
	virtual bool EndInteraction_Implementation() { return false; };

	/** Interaction Cancelled */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
	bool InteractionCancelled();
	virtual bool InteractionCancelled_Implementation() { return false; };

	/** Lookat Begin */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
	bool LookatBegin();
	virtual bool LookatBegin_Implementation() { return false; };

	/** Lookat End */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
	bool LookatEnd();
	virtual bool LookatEnd_Implementation() { return false; };
};