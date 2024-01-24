// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

class UArrowComponent;
class UBoxComponent;


class AObstacle;
class APickup;
class ATile;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTileExitSignature, ATile*, Tile);


UCLASS()
class OUTBREAK_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	

	ATile();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	const FTransform& GetAttachTransform() const;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	void SpawnObstacle();

	void SpawnPickups();

	UFUNCTION()
	void OnExitTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void DestroySelf();


protected:

	// Components.
	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	UArrowComponent* AttachPoint;

	UPROPERTY(EditAnywhere)
	UBoxComponent* ExitTrigger;


	UPROPERTY(EditAnywhere)
	TArray< TSubclassOf<AObstacle> > ObstacleTypes;

	UPROPERTY(EditAnywhere)
	TArray< TSubclassOf<APickup> > PickupTypes;


public:

	UPROPERTY(BlueprintAssignable)
	FTileExitSignature OnTileExit;
};
