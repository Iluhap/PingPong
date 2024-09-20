// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalTrigger.h"

#include "Ball.h"
#include "Components/ShapeComponent.h"
#include "GameFramework/GameStateBase.h"
#include "PingPong/GameMods/DefaultGameMode.h"
#include "PingPong/Player/BasePlayerState.h"


// Sets default values
AGoalTrigger::AGoalTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	PlayerID = 0;
}

// Called when the game starts or when spawned
void AGoalTrigger::BeginPlay()
{
	Super::BeginPlay();

	GetCollisionComponent()->OnComponentBeginOverlap.AddUniqueDynamic(this, &AGoalTrigger::OnBeginOverlap);

	if (auto* GameMode = Cast<ADefaultGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->OnGameStarted.AddUniqueDynamic(this, &AGoalTrigger::OnGameStarted);
	}
}

// Called every frame
void AGoalTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGoalTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
                                  AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                  bool bFromSweep, const FHitResult& SweepResult)
{
	if (const auto* Ball = Cast<ABall>(OtherActor); IsValid(Ball))
	{
		OnGoalTriggered.Broadcast();
	}
}

void AGoalTrigger::OnGameStarted()
{
	if (const auto* GameState = GetWorld()->GetGameState(); IsValid(GameState))
	{
		if (GameState->PlayerArray.Num() > PlayerID)
		{
			if (const auto* PlayerState = Cast<ABasePlayerState>(GameState->PlayerArray[PlayerID]);
				IsValid(PlayerState))
			{
				OnGoalTriggered.AddDynamic(PlayerState, &ABasePlayerState::IncrementScore);
			}
		}
	}
}

