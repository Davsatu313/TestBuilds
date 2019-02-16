// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyProjectGameMode.generated.h"

UCLASS(minimalapi)
class AMyProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyProjectGameMode();
	//*current camera angle*//
	float angle;
	//*current camera distance to player*//
	float distance;
	//*current game state*//
	int gameState;
	//*tick function called every frame *//
	//virtual void Tick(float DeltaTime) override;	
	//*Update the general Score*//
	void UpdateScore(float points);	
	//*If a point is spawned in the lvl update points variable*//
	void UpdatePoints(int state);

protected:
	virtual void BeginPlay() override;

private:
	//*the points in level*//
	int pointsInLevel;
	//*The game score *//
	float score;
};
