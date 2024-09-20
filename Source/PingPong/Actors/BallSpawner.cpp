﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "BallSpawner.h"

#include "Ball.h"


// Sets default values
ABallSpawner::ABallSpawner()
{
	BallClass = nullptr;
	BallRef = nullptr;
}

void ABallSpawner::DestroyBall_Implementation()
{
	if (IsValid(BallRef))
	{
		BallRef->Destroy();
	}
}

void ABallSpawner::SpawnBall_Implementation()
{
	DestroyBall();
	
	if (BallClass)
	{
		if (BallRef = Cast<ABall>(GetWorld()->SpawnActor(BallClass)); IsValid(BallRef))
		{
			GetWorld()->GetTimerManager().SetTimer(BallImpulseTimerHandle,
			                                       BallRef.Get(), &ABall::AddRandomImpulse,
			                                       BallImpulseDelay);
		}
	}
}
