// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactectable.h"
#include "Point.generated.h"

UCLASS()
class MYPROJECT_API APoint : public AActor, public IInteractectable
{
	GENERATED_BODY()
	
public:	
	//* Sets default values for this actor's properties *//
	APoint();
	//* Set the value of the point *//
	UPROPERTY(EditAnywhere)
		float points;

protected:
	//* Called when the game starts or when spawned *//
	virtual void BeginPlay() override;

private:
	class AMyProjectGameMode *gameMode;
	//*Tell game mode a point spawned *//
	void SpawnedPoint();
	void DoPlayerInteraction() override;
};
