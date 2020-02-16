// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Block.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyProjectCharacter.generated.h"

UCLASS(config=Game)
class AMyProjectCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyProjectCharacter();
	//set if the camera can move with the player
	UPROPERTY(EditAnywhere, Category = Camera)
		bool isFixedCamera;
	//set the camera angle
	UPROPERTY(EditAnywhere, Category = Camera)
		float cameraAngle;
	//set the camera distance to the player
	UPROPERTY(EditAnywhere, Category = Camera)
		float cameraLengthToPlayer;
	//instance of camera shake
	UPROPERTY(EditAnywhere)
		TSubclassOf<UCameraShake> myShake;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float timeToCollet;
	//*Count the times that a timer is called*//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float timerCalls;
	UPROPERTY(EditAnywhere)
		float blockDistanceFromThePlayer;
	//Set posible can pic up something
	bool onPause,canInteract;
	//Set the current time por the pause init
	float currTime;
	//Set the object that implements the interect functions
	class IInteractectable* interactObject;
	//*Game mode variable useful for all the world requirements*//
	class AMyProjectGameMode *gameMode;
	//* Returns CameraBoom subobject *//
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	//* Returns FollowCamera subobject *//
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
	//* Called for forwards/backward input *//
	void MoveForward(float Value);
	//* Called for side to side input *//
	void MoveRight(float Value);
	//* APawn interface *//
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime);
	
private:
	//* Camera Angles, set the camera angle to the target*//
	void IncreaseAngle();
	void DecreaseAngle();
	//* Camera lenght, set the camera distance to the target*//
	void DecreaseLenght();
	void IncreaseLenght();

	void FixedCamera();
	//* Restart game*//
	void RestartLevel();
	//*Interact with some Item*//
	void Interact();
	//*Put a block in the map*//
	void PutBlock();
	//*Stop interact with some Item*//
	void StopInteract();
	//*Pick if can*//
	void Pick();
	//*check if the interact key is pressed *//
	bool canPick;
	//*Overlap function, called when the actor ovelap something*//
	UFUNCTION()
		void OnOverlap(AActor * me, AActor * other);
	//*EndOverlap function, called when the actor end ovelaping something*//
	UFUNCTION()
		void EndOverlap(AActor * me, AActor * other);
	//*OnHit function, called when the actor hit something*//
	UFUNCTION()
		void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
	//* Camera boom positioning the camera behind the character *//
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;
	//* Follow camera *//
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;
	
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABlock> blockToSpawn;

	AActor * currentBlock;
};
