// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyTestCharacter.generated.h"

UCLASS()
class MYPROJECT_API AEnemyTestCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyTestCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(Editanywhere)
		TSubclassOf<class UStaticMesh> visioncone;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
