// Fill out your copyright notice in the Description page of Project Settings.


#include "RunGameMode.h"

#include "CppTranslated/Tile.h"


ARunGameMode::ARunGameMode()
	: NumInitialTiles(6)
	, CurrentTransform(FVector(-500.0, 0.0, 0.0))
{
	
}

void ARunGameMode::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < NumInitialTiles; i++)
	{
		SpawnTile();
	}
}

void ARunGameMode::SpawnTile()
{
	if (TileTypes.IsEmpty()) return;

	int randElem = FMath::Rand() % TileTypes.Num();
	ATile* tile = Cast<ATile>(GetWorld()->SpawnActor(TileTypes[randElem].Get(), &CurrentTransform));

	tile->OnTileExit.AddDynamic(this, &ARunGameMode::OnTileExit);

	CurrentTransform = tile->GetAttachTransform();
}

void ARunGameMode::OnTileExit(ATile* tile)
{
	SpawnTile();
}
