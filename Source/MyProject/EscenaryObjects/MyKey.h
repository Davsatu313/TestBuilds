// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactectable.h"
#include "MyKey.generated.h"


UCLASS()
class MYPROJECT_API AMyKey : public AActor,  public IInteractectable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyKey();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	class AMyProjectGameMode *gameMode;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//interaction with player
	void DoPlayerInteraction() override;

};
