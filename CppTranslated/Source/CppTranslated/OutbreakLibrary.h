// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "OutbreakLibrary.generated.h"

/**
 * 
 */
UCLASS()
class CPPTRANSLATED_API UOutbreakLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static int GetNumberOfCorridors();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float GetSpaceBetweenCorridors();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float GetCorridorY(int corridorIndex);
};
