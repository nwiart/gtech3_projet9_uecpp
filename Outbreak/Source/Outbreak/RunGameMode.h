// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RunGameMode.generated.h"

class ATile;


/**
 * 
 */
UCLASS()
class OUTBREAK_API ARunGameMode : public AGameModeBase
{
	GENERATED_BODY()
	

public:

	ARunGameMode();

	virtual void BeginPlay() override;

	void SpawnTile();

protected:

	UFUNCTION()
	void OnTileExit(ATile* tile);


private:

	UPROPERTY(EditAnywhere)
	TArray< TSubclassOf<ATile> > TileTypes;

	UPROPERTY(EditAnywhere)
	int NumInitialTiles;

	FTransform CurrentTransform;
};
