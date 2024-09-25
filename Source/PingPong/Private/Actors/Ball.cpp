// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Ball.h"


ABall::ABall()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Ball");
	Mesh->SetupAttachment(GetRootComponent());
	Mesh->SetSimulatePhysics(true);
}

void ABall::BeginPlay()
{
	Super::BeginPlay();
	Mesh->OnComponentHit.AddDynamic(this, &ABall::OnHit);
}

void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentVelocity = Mesh->GetComponentVelocity();
}

void ABall::OnHit(UPrimitiveComponent* HitComponent,
                  AActor* OtherActor, UPrimitiveComponent* OtherComp,
                  FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->Tags.Contains(ObstacleTag))
	{
		Mesh->SetPhysicsLinearVelocity(GetHitResultVelocity(Hit));
	}
}

void ABall::AddRandomImpulse()
{
	FVector Direction = FMath::VRand() * HitImpulseScale;
	Direction.Z = 0;

	Mesh->SetPhysicsLinearVelocity(Direction);
}

FVector ABall::GetHitResultVelocity(const FHitResult& Hit)
{
	FVector Velocity;

	if (CurrentVelocity.Length() != 0)
	{
		Velocity = CurrentVelocity - 2 * FVector::DotProduct(CurrentVelocity, Hit.ImpactNormal) * Hit.ImpactNormal;
		Velocity = Velocity.GetSafeNormal() * HitImpulseScale;
	}
	else  // In case Ball is not moving
	{
		Velocity = Hit.ImpactPoint * HitImpulseScale;
	}

	Velocity.Z = 0;

	return Velocity;
}

