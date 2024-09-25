// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/GoalTrigger.h"

#include "Actors/Ball.h"
#include "Components/ShapeComponent.h"
#include "GameFramework/GameStateBase.h"
#include "GameMods/DefaultGameMode.h"
#include "Player/BasePlayerState.h"


AGoalTrigger::AGoalTrigger()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	PlayerID = 0;
}

void AGoalTrigger::BeginPlay()
{
	Super::BeginPlay();

	GetCollisionComponent()->OnComponentBeginOverlap.AddUniqueDynamic(this, &AGoalTrigger::OnBeginOverlap);

	if (auto* GameMode = Cast<ADefaultGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->OnGameStarted.AddUniqueDynamic(this, &AGoalTrigger::OnGameStarted);
	}
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

