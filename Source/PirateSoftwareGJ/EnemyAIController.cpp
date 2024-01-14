// Copyright (c) 2024 GalaxyCat Studio Inc. All rights reserved.


#include "EnemyAIController.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"

AEnemyAIController::AEnemyAIController()
{

	perceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component"));
	
	sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));

	sightConfig->DetectionByAffiliation.bDetectEnemies = true;
	sightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	sightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	sightConfig->SightRadius = 400;
	sightConfig->LoseSightRadius = 800;
	sightConfig->PeripheralVisionAngleDegrees = 45.0f;
	
	perceptionComp->ConfigureSense(*sightConfig);
	perceptionComp->SetDominantSense(sightConfig->GetSenseImplementation());

	AAIController::SetGenericTeamId(FGenericTeamId(1));
	
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	perceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnTargetDetected);
	
	/** Check if pointer to behavior tree has been supplied in BP. */
	if (AIBehavior == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("SET THE Behavior Tree!!!!"));
		return;
	}

	/** Starts running the behavior tree. */
	RunBehaviorTree(AIBehavior);
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyAIController::OnTargetDetected(AActor* Actor, FAIStimulus const stimulus)
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Target Detected!"));

	if (!Actor->ActorHasTag("Player"))
		return;

	if (stimulus.WasSuccessfullySensed())
	{
		// Chase Player
		GetBlackboardComponent()->SetValueAsObject(TEXT("PlayerRef"), Actor);
		return;
	}

	// Lost track of player
	GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownLocation"), Actor->GetActorLocation());
	GetBlackboardComponent()->ClearValue(TEXT("PlayerRef"));
}
