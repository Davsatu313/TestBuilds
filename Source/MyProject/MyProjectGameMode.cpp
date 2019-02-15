// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "MyProjectGameMode.h"
#include "MyProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/HUD.h"
#define PLAYING 0
#define WIN 1
#define LOSE -1


AMyProjectGameMode::AMyProjectGameMode()
{
	//set tick enble
	//PrimaryActorTick.bCanEverTick = true;

	angle = 0;
	distance = 0;

	pointsInLevel = 0;
	score = 0.f;
	gameState = PLAYING;
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ProjectCharacterBP"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AMyProjectGameMode::BeginPlay()
{
	Super::BeginPlay();
}
/*
void AMyProjectGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Verify is are points 
	if (pointsInLevel == 0) {
		UE_LOG(LogTemp, Warning, TEXT("NO HAY PUNTOS \n"));
	}
}*/

void AMyProjectGameMode::UpdateScore(float points) {
	score += points;
	UE_LOG(LogTemp, Warning, TEXT("%f \n"), score);
}

void AMyProjectGameMode::UpdatePoints(int state) {
	pointsInLevel += state;
	if (pointsInLevel <= 0) {
		gameState = WIN;
	}
	//UE_LOG(LogTemp, Warning, TEXT("%d \n"), pointsInLevel);
}


