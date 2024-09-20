// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerState.h"

void ABasePlayerState::BeginPlay()
{
	Super::BeginPlay();

	ScoreCount = 0;
}

int32 ABasePlayerState::GetScoreCount() const
{
	return ScoreCount;
}

void ABasePlayerState::IncrementScore_Implementation()
{
	ScoreCount++;

	UE_LOG(LogTemp, Warning, TEXT("Player %s Score: %d"), *GetPlayerName(), ScoreCount);
}