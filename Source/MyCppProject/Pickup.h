// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

class ARunCharacter;

UCLASS()
class MYCPPPROJECT_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

protected:

	virtual void BeginPlay() override;

	// Event for when the player hits this pickup.
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnHit"))
	void ReceiveOnHit(ARunCharacter* RunCharacter);

	virtual void OnHit(ARunCharacter* RunCharacter);


private:

	UFUNCTION()
	void OnMeshBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


protected:

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	USoundBase* PickupSound;
};
