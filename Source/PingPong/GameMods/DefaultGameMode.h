// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "DefaultGameMode.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRoundStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRoundEnd);

UCLASS()
class PINGPONG_API ADefaultGameMode : public AGameMode
{
	GENERATED_BODY()

	ADefaultGameMode();

public:
	virtual void StartPlay() override;
	
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

private:
	UFUNCTION()
	void StartRound();

	UFUNCTION()
	void StopRound();

	UFUNCTION()
	void RestartRound();

public:
	virtual void Tick(float DeltaSeconds) override;

private:
	void CheckGameEnd();
	void EndGame(const APlayerController* WinningPlayer);
	void QuitGame();

public:
	FRoundStart OnGameStarted;
	FRoundStart OnRoundStarted;
	FRoundEnd OnRoundEnd;
	
private:
	UPROPERTY()
	int32 PlayerCount = 0;

	UPROPERTY(EditDefaultsOnly, Category="Configuration", meta=(AllowPrivateAccess="true"))
	int32 ScoreLimit = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Configuration", meta=(AllowPrivateAccess="true"))
	float RoundStartDelay = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Configuration", meta=(AllowPrivateAccess="true"))
	float QuitGameDelay = 5.f;

	UPROPERTY()
	FTimerHandle RoundStartTimerHandle;

	UPROPERTY()
	FTimerHandle QuitGameTimerHandle;
};
