// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyProjectCharacter.generated.h"

UCLASS(config=Game)
class AMyProjectCharacter : public ACharacter
{
	GENERATED_BODY()

	//* Camera boom positioning the camera behind the character *//
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	//* Follow camera *//
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;
public:
	AMyProjectCharacter();

	UPROPERTY(EditAnywhere, Category = Camera)
		bool isFixedCamera;
	UPROPERTY(EditAnywhere, Category = Camera)
		float cameraAngle;
	UPROPERTY(EditAnywhere, Category = Camera)
		float cameraLengthToPlayer;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UCameraShake> myShake;

	bool onPause,canPickUp;
	float currTime;
	class APoint* pickPoint;
	

	class AMyProjectGameMode *gameMode;

protected:

	//* Called for forwards/backward input *//
	void MoveForward(float Value);

	//* Called for side to side input *//
	void MoveRight(float Value);

protected:
	//* APawn interface *//
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime);
	
private:
	//* Camera Angles*//
	void IncreaseAngle();
	void DecreaseAngle();
	//* Camera lenght*//
	void DecreaseLenght();
	void IncreaseLenght();
	//* Restart game*//
	void RestartLevel();
	//*Pick up Item*//
	void PickUp();
	//*Overlap function*//
	UFUNCTION()
		void OnOverlap(AActor * me, AActor * other);
	UFUNCTION()
		void EndOverlap(AActor * me, AActor * other);
	UFUNCTION()
		void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

public:
	//* Returns CameraBoom subobject *//
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	//* Returns FollowCamera subobject *//
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

