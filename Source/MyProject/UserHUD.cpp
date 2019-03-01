// Fill out your copyright notice in the Description page of Project Settings.

#include "UserHUD.h"
#include "Engine/World.h"
#include "Components/TextBlock.h"
#include "MyProjectGameMode.h"
#include "MyProjectCharacter.h"
#define PLAYING 0
#define WIN 1
#define LOSE -1

void UUserHUD::NativeTick(const FGeometry & geometry, float InDeltaTime)
{
	Super::NativeTick(geometry, InDeltaTime);

	//set the text bloc games

	if (gameMode->gameState != PLAYING) {
		if (gameMode->gameState == WIN) {
			EndGame->SetText(FText::FromString("WIN"));
		}
		else {
			EndGame->SetText(FText::FromString("LOSE"));
		}
		Restart->SetText(FText::FromString("PRESS SPACE BAR FOR RESTART"));
	}

}

//*convert a float type into a FText type for UI*//
FText UUserHUD::FloatToText(float parameter)
{
	FString parameterString = FString::SanitizeFloat(parameter);
	FText parameterText = FText::FromString(parameterString);
	return parameterText;
}


void UUserHUD::NativeConstruct()
{
	Super::NativeConstruct();
	UE_LOG(LogTemp, Warning, TEXT("HOLA \n"));
	//Get the game mode an verify if exist
	AGameModeBase* mode = GetWorld()->GetAuthGameMode();
	if (mode != nullptr) {
		gameMode = Cast<AMyProjectGameMode>(mode);
	}

}