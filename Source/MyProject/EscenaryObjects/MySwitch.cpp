// Fill out your copyright notice in the Description page of Project Settings.

#include "MySwitch.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Materials/Material.h"
#include "Engine/StaticMesh.h"
#include "DoorWithSwitch.h"
#define OFF 1
#define ON -1

// Sets default values
AMySwitch::AMySwitch()
{
	

}

void AMySwitch::OnOverlap(AActor * me, AActor * other)
{
	if (myDoor != nullptr) {
		myDoor->setActiveSwitch(ON);
		//this->Destroy();
		bIsActive = true;
	}

}

void AMySwitch::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this,&AMySwitch::OnOverlap);
	if (myDoor != nullptr) {
		myDoor->setnumSwitch(OFF);
	}
	else
	{
		this->Destroy();
	}
}
