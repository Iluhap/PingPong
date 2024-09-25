// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Components/ObstacleMovement.h"

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

	if (const auto* Character = Cast<ACharacter>(GetOwner()); IsValid(Character))
	{
		Character->GetCharacterMovement()->MaxWalkSpeed = Speed;
	}
	
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

	if (auto* Character = Cast<ACharacter>(GetOwner()); IsValid(Character))
	{
		const FRotator PlayerRotation = Character->GetControlRotation();
		const FVector RightDirection = FRotationMatrix(PlayerRotation).GetScaledAxis(EAxis::Y);

		Character->AddMovementInput(RightDirection, InputValue * Speed);
	}
}

UStaticMeshComponent* UObstacleMovement::GetObstacle() const
{
	if (const auto* Owner = GetOwner(); Owner)
	{
		return Owner->FindComponentByClass<UStaticMeshComponent>();
	}
	return nullptr;
}
