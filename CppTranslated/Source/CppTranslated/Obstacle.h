// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacle.generated.h"

class ARunCharacter;


UCLASS()
class CPPTRANSLATED_API AObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacle();

protected:
	
	virtual void BeginPlay() override;

	// Event for when the player hits this obstacle.
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnHit"))
	void ReceiveOnHit(ARunCharacter* RunCharacter);

	virtual void OnHit(ARunCharacter* RunCharacter);


private:

	UFUNCTION()
	void OnMeshHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


protected:

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;
};
