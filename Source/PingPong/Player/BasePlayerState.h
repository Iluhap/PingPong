// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BasePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG_API ABasePlayerState : public APlayerState
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(NetMulticast, Reliable)
	void IncrementScore();

	UFUNCTION(BlueprintCallable)
	int32 GetScoreCount() const;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Score", meta=(AllowPrivateAccess = "true"))
	int32 ScoreCount = 0;
};
