// Fill out your copyright notice in the Description page of Project Settings.


#include "RunCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
ARunCharacter::ARunCharacter()
	: DeathParticles(NULL)
	, DeathSound(NULL)
	, StrafeSpeed(1000.0F)
	, DesiredCorridor(2)
	, bIsDead(false)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");

	SpringArm->SetupAttachment(this->GetRootComponent());
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ARunCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARunCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsDead) return;

	// Perpetual forward motion.
	AddMovementInput(FVector(1.0, 0.0, 0.0));

	// Slide sideways when switching corridors.
	FVector location = GetActorLocation();
	float desiredCorridorY = DesiredCorridor * 200.0F - 400.0F;
	if (FMathf::Abs(desiredCorridorY - location.Y) > 5.0F)
	{
		float offset = FMathf::Sign(desiredCorridorY - location.Y) * StrafeSpeed * DeltaTime;

		SetActorLocation(location + FVector(0.0, offset, 0.0));
	}
}

// Called to bind functionality to input
void ARunCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ARunCharacter::StrafeLeft()
{
	if (DesiredCorridor == 0) return;

	DesiredCorridor--;
}

void ARunCharacter::StrafeRight()
{
	if (DesiredCorridor == 4) return;

	DesiredCorridor++;
}


void ARunCharacter::Die()
{
	if (bIsDead) return;

	bIsDead = true;

	GetCharacterMovement()->StopMovementImmediately();
	DisableInput(NULL);

	// Spawn particle effect.
	if (DeathParticles) UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathParticles, FTransform(GetActorLocation()));

	// Play sound.
	if (DeathSound) UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());

	GetMesh()->SetVisibility(false);
}
