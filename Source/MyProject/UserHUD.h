 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserHUD.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UUserHUD : public UUserWidget
{
	GENERATED_BODY()
public:
	//*Natve functions of UI*//
	void NativeConstruct() override;
	void NativeTick(const FGeometry& geometry, float InDeltaTime) override;

private:
	//*Game mode pointer*//
	class AMyProjectGameMode* gameMode;
	//*UI Elements*//
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* AngleBlock;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* DistanceBlock;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* EndGame;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Restart;
	//*Update UI functions*//
	FText FloatToText(float angle);	
};
