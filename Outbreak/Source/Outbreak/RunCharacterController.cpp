// Fill out your copyright notice in the Description page of Project Settings.


#include "RunCharacterController.h"

#include "Outbreak/RunCharacter.h"

#include "Kismet/GameplayStatics.h"


ARunCharacterController::ARunCharacterController()
	: RunCharacter(0)
{
	EnableInput(this);
	AutoReceiveInput = EAutoReceiveInput::Player0;
}

void ARunCharacterController::BeginPlay()
{
	Super::BeginPlay();

	RunCharacter = Cast<ARunCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
}

void ARunCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("StrafeLeft", EInputEvent::IE_Pressed, this, &ARunCharacterController::StrafeLeft);
	InputComponent->BindAction("StrafeRight", EInputEvent::IE_Pressed, this, &ARunCharacterController::StrafeRight);
}


void ARunCharacterController::StrafeLeft()
{
	RunCharacter->StrafeLeft();
}

void ARunCharacterController::StrafeRight()
{
	RunCharacter->StrafeRight();
}
