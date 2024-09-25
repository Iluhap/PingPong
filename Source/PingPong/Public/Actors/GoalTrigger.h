// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "GoalTrigger.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGoalTriggered);

UCLASS()
class PINGPONG_API AGoalTrigger : public ATriggerBox
{
	GENERATED_BODY()

public:
	AGoalTrigger();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	                    AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	                    bool bFromSweep, const FHitResult& SweepResult);


	UFUNCTION()
	void OnGameStarted();
	
public:
	FGoalTriggered OnGoalTriggered;

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Player", meta=(AllowPrivateAccess = "true"))
	int32 PlayerID;
};
