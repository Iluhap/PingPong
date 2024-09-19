// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/ObstacleMovement.h"
#include "GameFramework/Character.h"


void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetupInput();
}

void ABasePlayerController::SetupInput()
{
	if (auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	if (auto* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent); IsValid(EnhancedInputComponent))
	{
		if (const auto* CharacterRef = GetCharacter(); IsValid(CharacterRef))
		{
			if (auto* Movement = CharacterRef->FindComponentByClass<UObstacleMovement>(); IsValid(Movement))
			{
				EnhancedInputComponent->BindAction(MoveAction,
												   ETriggerEvent::Triggered, Movement,
												   &UObstacleMovement::Move);
			}
		}
	}
}
