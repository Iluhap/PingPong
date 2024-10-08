﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

UCLASS()
class PINGPONG_API ABall : public AActor
{
	GENERATED_BODY()

public:
	ABall();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent,
	           AActor* OtherActor, UPrimitiveComponent* OtherComp,
	           FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void AddRandomImpulse();

private:
	FVector GetHitResultVelocity(const FHitResult& Hit);
	
private:
	UPROPERTY(EditDefaultsOnly, Category="Mesh", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category="Tags", meta=(AllowPrivateAccess = "true"))
	FName ObstacleTag;

	UPROPERTY(EditDefaultsOnly, Category="Physics", meta=(AllowPrivateAccess = "true"))
	float HitImpulseScale = 1000;

	UPROPERTY()
	FVector CurrentVelocity;
};
