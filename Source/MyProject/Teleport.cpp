// Fill out your copyright notice in the Description page of Project Settings.

#include "Teleport.h"
#include "MyProjectCharacter.h"

// Called when the game starts or when spawned
void ATeleport::BeginPlay()
{
	Super::BeginPlay();

	if (target != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("EXISTO"))
			targetLocation = target->GetActorLocation();
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("NO TENGO DESTINO"))
	}
	OnActorBeginOverlap.AddDynamic(this, &ATeleport::OnOverlap);
}

void ATeleport::OnOverlap(AActor * me, AActor * other)
{
	AMyProjectCharacter *player = Cast<AMyProjectCharacter>(other);
	if (player != nullptr) {
		player->SetActorLocation(targetLocation);
	}
}



