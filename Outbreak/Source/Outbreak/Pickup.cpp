// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"

#include "Outbreak/RunCharacter.h"

#include "GameFramework/RotatingMovementComponent.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
APickup::APickup()
	: PickupSound(0)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* DefaultRoot = CreateDefaultSubobject<USceneComponent>("DefaultSceneRoot");
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	URotatingMovementComponent* Rotating = CreateDefaultSubobject<URotatingMovementComponent>("RotatingMovement");

	// Set static mesh to overlap pawns only.
	FCollisionResponseContainer collisionResponse;
	collisionResponse.SetAllChannels(ECollisionResponse::ECR_Ignore);
	collisionResponse.SetResponse(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	StaticMesh->SetCollisionResponseToChannels(collisionResponse);

	// Setup component attachment.
	this->SetRootComponent(DefaultRoot);
	StaticMesh->SetupAttachment(DefaultRoot);
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnMeshBeginOverlap);
}

void APickup::OnHit(ARunCharacter* RunCharacter)
{
	ReceiveOnHit(RunCharacter);
}

void APickup::OnMeshBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if player hit the mesh.
	if (OtherActor != (AActor*) UGameplayStatics::GetPlayerCharacter(this, 0)) return;

	ARunCharacter* character = Cast<ARunCharacter>(OtherActor);
	//if (!character) return;

	OnHit(character);

	if (PickupSound) {
		UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
	}

	Destroy();
}
