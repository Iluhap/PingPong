// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayer.h"

#include "Camera/CameraComponent.h"
#include "Components/ObstacleMovement.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
ABasePlayer::ABasePlayer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Obstacle = CreateDefaultSubobject<UStaticMeshComponent>("Obstacle");
	Obstacle->SetupAttachment(GetRootComponent());

	Movement = CreateDefaultSubobject<UObstacleMovement>("Movement");

	CameraArm = CreateDefaultSubobject<USpringArmComponent>("CameraArm");
	CameraArm->SetupAttachment(GetRootComponent());
	CameraArm->TargetArmLength = 2000.f;
	
	// Create a CameraComponent	
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(CameraArm);
}

// Called when the game starts or when spawned
void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();

	CameraArm->SetWorldLocation(GetActorLocation());
	CameraArm->SetRelativeRotation(FRotator {-40, 0, 0});
	CameraArm->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
}

// Called every frame
void ABasePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

