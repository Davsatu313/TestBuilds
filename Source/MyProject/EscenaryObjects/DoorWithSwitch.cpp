// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorWithSwitch.h"

ADoorWithSwitch::ADoorWithSwitch()
{
	numSwitch = 0;
}

void ADoorWithSwitch::setnumSwitch(int arg)
{
	numSwitch += arg;
}

void ADoorWithSwitch::setActiveSwitch(int arg)
{
	numSwitch += arg;
	if (numSwitch <= 0 && move == false) {
		move = true;
	}
	else if (numSwitch >= 0 && move == true){
		move = false;
	}
}

void ADoorWithSwitch::Tick(float DeltaTime)
{
	FVector actual = GetActorLocation();
	if (move) {
		AddActorLocalOffset(FVector(0, 0, downVelocity)*DeltaTime);
	}
	if (actual.Z <= deletePosition && move != false) {
		move = false;
	}
	if (actual.Z < initialPosition.Z && numSwitch > 0) {
		AddActorLocalOffset(FVector(0, 0, downVelocity * -1 )*DeltaTime);
	}

}

//do nothing at this moment
void ADoorWithSwitch::DoPlayerInteraction()
{
}
