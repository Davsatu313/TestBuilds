// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EscenaryObjects/MyDoor.h"
#include "DoorWithKey.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API ADoorWithKey : public AMyDoor
{
	GENERATED_BODY()
	void DoPlayerInteraction() override;
	
};
