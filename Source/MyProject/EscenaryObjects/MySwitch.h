// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "DoorWithSwitch.h"
#include "MySwitch.generated.h"



UCLASS()
class MYPROJECT_API AMySwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMySwitch();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
	virtual void OnOverlap(AActor * me, AActor * other) ;

	UPROPERTY(Editanywhere)
		class ADoorWithSwitch * myDoor;
};
