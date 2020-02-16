// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PressionSwitch.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API APressionSwitch : public AActor
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION()
		void OnOverlap(AActor * me, AActor * other) ;

	UFUNCTION()
		void EndOverlap(AActor * me, AActor * other);

	UPROPERTY(Editanywhere)
		class ADoorWithSwitch * myDoor;
	
};
