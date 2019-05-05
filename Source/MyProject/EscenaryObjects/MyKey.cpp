// Fill out your copyright notice in the Description page of Project Settings.
#include "MyKey.h"
#include "Engine/World.h"
#include "MyProjectGameMode.h"
#include "Interfaces/Interactectable.h"

#define TAKEN 1


// Sets default values
AMyKey::AMyKey()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyKey::BeginPlay()
{
	gameMode = GetWorld()->GetAuthGameMode<AMyProjectGameMode>();
	Super::BeginPlay();
	
}

// Called every frame
void AMyKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyKey::DoPlayerInteraction()
{
	gameMode->SetRecolectedKeys(TAKEN);
	this->Destroy();	
}

