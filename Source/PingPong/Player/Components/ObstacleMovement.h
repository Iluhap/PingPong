// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObstacleMovement.generated.h"


class UCharacterMovementComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PINGPONG_API UObstacleMovement : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UObstacleMovement();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

public:
	void Move(const struct FInputActionValue& Value);

private:
	UStaticMeshComponent* GetObstacle();

private:
	UPROPERTY(EditAnywhere, Category="Params", meta=(AllowPrivateAccess = "true"))
	float Speed = 100;

	UPROPERTY(EditAnywhere, Category="Params", meta=(AllowPrivateAccess = "true"))
	float EdgeDistance = 1000;

	UPROPERTY()
	FVector StartLocation;
};
