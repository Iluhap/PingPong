// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BallSpawner.generated.h"

class ABall;

UCLASS()
class PINGPONG_API ABallSpawner : public AActor
{
	GENERATED_BODY()

public:
	ABallSpawner();

public:
	UFUNCTION(NetMulticast, Reliable)
	void SpawnBall();

	UFUNCTION(NetMulticast, Reliable)
	void DestroyBall();
	
private:
	UPROPERTY(EditAnywhere, Category="Ball", meta=(AllowPrivateAccess="true"))
	TSubclassOf<ABall> BallClass;

	UPROPERTY(EditAnywhere, Category="Ball", meta=(AllowPrivateAccess="true"))
	float BallImpulseDelay = 2.f;
	
	UPROPERTY()
	TObjectPtr<ABall> BallRef;

	UPROPERTY()
	FTimerHandle BallImpulseTimerHandle;
	
};
