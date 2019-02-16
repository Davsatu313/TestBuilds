// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Teleport.generated.h"

UCLASS()
class MYPROJECT_API ATeleport : public AActor
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FVector targetLocation;
	//*Actor where supose to be teleported*//
	UPROPERTY(EditAnywhere)
		AActor* target;
	//*Teleporting logic when overlap happends*//
	UFUNCTION()
		void OnOverlap(AActor *me, AActor * other);
};
