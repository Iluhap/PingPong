// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayer.h"

#include "Camera/CameraComponent.h"
#include "Components/ObstacleMovement.h"
#include "GameFramework/SpringArmComponent.h"


ABasePlayer::ABasePlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	Obstacle = CreateDefaultSubobject<UStaticMeshComponent>("Obstacle");
	Obstacle->SetupAttachment(GetRootComponent());

	Movement = CreateDefaultSubobject<UObstacleMovement>("Movement");

	CameraArm = CreateDefaultSubobject<USpringArmComponent>("CameraArm");
	CameraArm->SetupAttachment(GetRootComponent());
	CameraArm->TargetArmLength = 2000.f;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(CameraArm);
}

void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();

	CameraArm->SetWorldLocation(GetActorLocation());
	CameraArm->SetRelativeRotation(FRotator {-40, 0, 0});
	CameraArm->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
}

