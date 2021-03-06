// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interfaces/Interactectable.h"
//#include "DoorWithSwitch.h"
#include "MySwitch.generated.h"



UCLASS()
class MYPROJECT_API AMySwitch : public APawn, public IInteractectable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMySwitch();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	void DoPlayerInteraction() override;

	UPROPERTY(Editanywhere)
		class ADoorWithSwitch * myDoor;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = MySwitch)
		bool bIsActive;
};
