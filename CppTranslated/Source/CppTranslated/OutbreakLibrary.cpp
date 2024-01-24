// Fill out your copyright notice in the Description page of Project Settings.


#include "OutbreakLibrary.h"


int UOutbreakLibrary::GetNumberOfCorridors()
{
	return 5;
}

float UOutbreakLibrary::GetSpaceBetweenCorridors()
{
	return 200.0F;
}

float UOutbreakLibrary::GetCorridorY(int corridorIndex)
{
	return corridorIndex * GetSpaceBetweenCorridors() - 400.0F;
}
