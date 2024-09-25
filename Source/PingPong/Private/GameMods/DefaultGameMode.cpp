// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMods/DefaultGameMode.h"

#include "EngineUtils.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Actors/BallSpawner.h"
#include "Actors/GoalTrigger.h"
#include "Player/BasePlayerState.h"

class ABasePlayerState;

ADefaultGameMode::ADefaultGameMode()
{
	PlayerCount = 0;
	ScoreLimit = 5;
}

void ADefaultGameMode::StartPlay()
{
	Super::StartPlay();

	for (auto* GoalTrigger : TActorRange<AGoalTrigger>(GetWorld()))
	{
		GoalTrigger->OnGoalTriggered.AddDynamic(this, &ADefaultGameMode::RestartRound);
	}

	for (auto* BallSpawner : TActorRange<ABallSpawner>(GetWorld()))
	{
		OnRoundStarted.AddUniqueDynamic(BallSpawner, &ABallSpawner::SpawnBall);
		OnRoundEnd.AddUniqueDynamic(BallSpawner, &ABallSpawner::DestroyBall);
	}

	UE_LOG(LogTemp, Warning, TEXT("Game is starting... Waiting for players."));
}

void ADefaultGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	PlayerCount++;

	if (PlayerCount == PlayersCountToStart)
	{
		OnGameStarted.Broadcast();
		StartRound();
	}
}

void ADefaultGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	PlayerCount--;
	UE_LOG(LogTemp, Warning, TEXT("Player left. Current player count: %d"), PlayerCount);

	if (PlayerCount < PlayersCountToStart)
	{
		UE_LOG(LogTemp, Warning, TEXT("Game stopped due to player disconnection."));
		StopRound();
	}
}

void ADefaultGameMode::StartRound()
{
	OnRoundStarted.Broadcast();
}

void ADefaultGameMode::StopRound()
{
	OnRoundEnd.Broadcast();
}

void ADefaultGameMode::RestartRound()
{
	StopRound();
	GetWorld()->GetTimerManager().SetTimer(RoundStartTimerHandle,
	                                       this, &ADefaultGameMode::StartRound, RoundStartDelay);
}

void ADefaultGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CheckGameEnd();
}

void ADefaultGameMode::CheckGameEnd()
{
	for (const auto* PlayerController : TActorRange<APlayerController>(GetWorld()))
	{
		if (const auto* PlayerState = PlayerController->GetPlayerState<ABasePlayerState>();
			IsValid(PlayerState) && PlayerState->GetScoreCount() >= ScoreLimit)
		{
			StopRound();
			EndGame(PlayerController);
		}
	}
}

void ADefaultGameMode::EndGame(const APlayerController* WinningPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("Game Over! Player %s won!"), *WinningPlayer->GetName());

	if (auto& TimerManager = GetWorld()->GetTimerManager();
		!TimerManager.IsTimerActive(QuitGameTimerHandle))
	{
		TimerManager.SetTimer(QuitGameTimerHandle,
		                      this, &ADefaultGameMode::QuitGame, QuitGameDelay);
	}
}

void ADefaultGameMode::QuitGame()
{
	for (auto* PlayerController: TActorRange<APlayerController>(GetWorld()))
	{
		UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, true);	
	}
}
