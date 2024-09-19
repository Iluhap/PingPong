// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleMovement.h"

#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values for this component's properties
UObstacleMovement::UObstacleMovement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UObstacleMovement::BeginPlay()
{
	Super::BeginPlay();

	auto* Character = Cast<ACharacter>(GetOwner());

	Character->GetCharacterMovement()->MaxWalkSpeed = Speed;
	
	if (const auto* Obstacle = GetObstacle(); IsValid(Obstacle))
	{
		StartLocation = Obstacle->GetRelativeLocation();
	}
}

// Called every frame
void UObstacleMovement::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UObstacleMovement::Move(const FInputActionValue& Value)
{
	const float InputValue = Value.Get<float>();

	const float LeftBound = StartLocation.Y - EdgeDistance;
	const float RightBound = StartLocation.Y + EdgeDistance;

	if (auto* Pawn = Cast<APawn>(GetOwner()); IsValid(Pawn))
	{
		const FRotator PlayerRotation = Pawn->GetControlRotation();
		const FVector RightDirection = FRotationMatrix(PlayerRotation).GetScaledAxis(EAxis::Y);

		Pawn->AddMovementInput(RightDirection, InputValue);
	}
	
	if (auto* Obstacle = GetObstacle(); IsValid(Obstacle))
	{
		const FVector CurrentLocation = Obstacle->GetRelativeLocation();
		const FVector NewLocation = {
			CurrentLocation.X,
			FMath::Clamp(CurrentLocation.Y + InputValue, LeftBound, RightBound),
			CurrentLocation.Z
		};
		
		// Obstacle->SetRelativeLocation(NewLocation, true);
	}
}

UStaticMeshComponent* UObstacleMovement::GetObstacle()
{
	if (const auto* Owner = GetOwner(); Owner)
	{
		return Owner->FindComponentByClass<UStaticMeshComponent>();
	}
	return nullptr;
}
