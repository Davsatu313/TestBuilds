// Fill out your copyright notice in the Description page of Project Settings.

#include "Point.h"
#include "Engine/World.h"
#include "MyProjectGameMode.h"
#include "MainCharacter/MyProjectCharacter.h"
#include "Interfaces/Interactectable.h"

#define SPAWNED 1
#define TAKEN -1
// Sets default values
APoint::APoint()
{
	points = 10.0f;

}

// Called when the game starts or when spawned
void APoint::BeginPlay()
{
	Super::BeginPlay();
	SpawnedPoint();
}

void APoint::SpawnedPoint() {
	gameMode = GetWorld()->GetAuthGameMode<AMyProjectGameMode>();
	gameMode->UpdatePoints(SPAWNED);
}

void APoint::DoPlayerInteraction()
{
	gameMode->UpdateScore(points);
	gameMode->UpdatePoints(TAKEN);
	this->Destroy();
}
