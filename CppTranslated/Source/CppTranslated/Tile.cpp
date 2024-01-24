// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"

#include "Kismet/GameplayStatics.h"

#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

#include "CppTranslated/OutbreakLibrary.h"


ATile::ATile()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>("SceneRoot");
	AttachPoint = CreateDefaultSubobject<UArrowComponent>("AttachPoint");
	ExitTrigger = CreateDefaultSubobject<UBoxComponent>("ExitTrigger");

	this->SetRootComponent(Root);
	AttachPoint->SetupAttachment(Root);
	ExitTrigger->SetupAttachment(Root);
}

const FTransform& ATile::GetAttachTransform() const
{
	return AttachPoint->GetComponentTransform();
}


// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();

	ExitTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATile::OnExitTriggerEnter);
}

void ATile::SpawnObstacle()
{
	if (ObstacleTypes.IsEmpty()) return;

	int randElem = FMath::Rand() % ObstacleTypes.Num();

	float Y = UOutbreakLibrary::GetCorridorY(FMath::Rand() % UOutbreakLibrary::GetNumberOfCorridors());

	FVector Location(0.0, Y, 0.0);
	GetWorld()->SpawnActor(ObstacleTypes[randElem].Get(), &Location, &FRotator::ZeroRotator);
}

void ATile::SpawnPickups()
{

}

void ATile::OnExitTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!player) {
		UE_LOG(LogTemp, Error, TEXT("Player is null!"));
	}

	if (OtherActor == (AActor*) player)
	{
		OnTileExit.Broadcast(this);

		// Destroy after 1 second.
		FTimerHandle handle;
		GetWorldTimerManager().SetTimer(handle, FTimerDelegate::CreateUObject(this, &ATile::DestroySelf), 1.0F, false);
	}
}

void ATile::DestroySelf()
{
	Destroy();
}
