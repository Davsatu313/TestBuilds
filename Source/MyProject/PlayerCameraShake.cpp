// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCameraShake.h"

UPlayerCameraShake::UPlayerCameraShake() {
	OscillationDuration = 0.2;
	OscillationBlendInTime = 0.05;
	OscillationBlendOutTime = 0.05;

	RotOscillation.Pitch.Amplitude = FMath::RandRange(1.0f, 3.0f);
	RotOscillation.Pitch.Frequency = FMath::RandRange(1.0f, 3.0f);
	
	RotOscillation.Yaw.Amplitude = FMath::RandRange(1.0f, 3.0f);
	RotOscillation.Yaw.Frequency = FMath::RandRange(1.0f, 3.0f);

		
}