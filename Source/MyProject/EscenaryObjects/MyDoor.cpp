// Fill out your copyright notice in the Description page of Project Settings.

#include "MyDoor.h"
#include "Interfaces/Interactectable.h"
#include "Engine/World.h"
#include "MyProjectGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyDoor::AMyDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	move = false;
	downVelocity = -100.0;
	deletePosition = -10.0;

}

// Called when the game starts or when spawned
void AMyDoor::BeginPlay()
{
	gameMode = GetWorld()->GetAuthGameMode<AMyProjectGameMode>();
	Super::BeginPlay();
	
}

// Called every frame
void AMyDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector actual = GetActorLocation();
	if (move) {
		AddActorLocalOffset(FVector(0,0, downVelocity)*DeltaTime);
	}
	if (actual.Z <= deletePosition) {
		UE_LOG(LogTemp, Warning, TEXT("Deleting A Door \n"));
		this->Destroy();
	}

}

void AMyDoor::DoPlayerInteraction()
{
	/*Mover la puerta */
	move = true;
	UE_LOG(LogTemp, Warning, TEXT("Opening A Door \n"));
	
}

