// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RunCharacterController.generated.h"

class ARunCharacter;


UCLASS()
class CPPTRANSLATED_API ARunCharacterController : public APlayerController
{
	GENERATED_BODY()
	
public:

	ARunCharacterController();

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	UFUNCTION()
	void StrafeLeft();

	UFUNCTION()
	void StrafeRight();


private:

	ARunCharacter* RunCharacter;
};
