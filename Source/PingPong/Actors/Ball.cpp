// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"


// Sets default values
ABall::ABall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Ball");
	Mesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	Mesh->OnComponentHit.AddDynamic(this, &ABall::OnHit);
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentVelocity = Mesh->GetComponentVelocity();

	const FVector BodyCenter = Mesh->GetCenterOfMass();
	DrawDebugDirectionalArrow(GetWorld(),
	                          BodyCenter, BodyCenter + CurrentVelocity.GetSafeNormal() * 200,
	                          10, FColor::Yellow, false, 0.1);


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

