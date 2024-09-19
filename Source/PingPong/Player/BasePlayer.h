// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "BasePlayer.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UObstacleMovement;

UCLASS()
class PINGPONG_API ABasePlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABasePlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Obstacle", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Obstacle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UObstacleMovement> Movement;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Camera", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Camera", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> Camera;
	
};
