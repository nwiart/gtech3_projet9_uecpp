// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"

#include "Outbreak/RunCharacter.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
AObstacle::AObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* DefaultRoot = CreateDefaultSubobject<USceneComponent>("DefaultSceneRoot");
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");

	// Set hit events to trigger.
	StaticMesh->SetNotifyRigidBodyCollision(true);

	this->SetRootComponent(DefaultRoot);
	StaticMesh->SetupAttachment(DefaultRoot);
}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();

	StaticMesh->OnComponentHit.AddDynamic(this, &AObstacle::OnMeshHit);
}

void AObstacle::OnHit(ARunCharacter* RunCharacter)
{
	ReceiveOnHit(RunCharacter);
}

void AObstacle::OnMeshHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != (AActor*) UGameplayStatics::GetPlayerCharacter(this, 0)) return;

	ARunCharacter* character = Cast<ARunCharacter>(OtherActor);
	if (!character) return;

	OnHit(character);
}
