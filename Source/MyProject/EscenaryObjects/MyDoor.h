// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactectable.h"
#include "MyDoor.generated.h"

UCLASS()
class MYPROJECT_API AMyDoor : public AActor, public IInteractectable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	class AMyProjectGameMode *gameMode;
	FVector initialPosition;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//interaction with player
	void DoPlayerInteraction() override;

	UPROPERTY(EditAnywhere)
		float downVelocity;
	UPROPERTY(EditAnywhere)
		float deletePosition;

	bool move;
private:
	

};
