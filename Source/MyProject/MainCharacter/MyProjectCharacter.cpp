// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "MyProjectCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Enemies/EnemyTestCharacter.h"
#include "Items/Point.h"
#include "EscenaryObjects/MyDoor.h"
#include "PlayerCameraShake.h"
#include "Engine/World.h"
#include "MyProjectGameMode.h"
#include "Kismet/GameplayStatics.h"

#define TIMERCALLING 0.1f
#define PLAYING 0
#define WIN 1
#define LOSE -1
//////////////////////////////////////////////////////////////////////////
// AMyProjectCharacter

AMyProjectCharacter::AMyProjectCharacter()
{
	//pause flag
	onPause = true;
	currTime = 0;	
	//PickUp flag
	canInteract = false;
	//Set the camera debug variables
	isFixedCamera = false;
	cameraAngle = -70.0f;
	cameraLengthToPlayer = 600.0f;
	//collec default time
	timeToCollet = 2.0f;
	canPick = false;
	timerCalls = 0.0f;
	//block variables
	blockDistanceFromThePlayer = 100.0f;

	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = cameraLengthToPlayer;
	CameraBoom->RelativeRotation = FRotator(cameraAngle, 0.f, 0.f);
	CameraBoom->bAbsoluteLocation = isFixedCamera; //Don't want arm to move, is fixed camera
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

}
//////////////////////////////////////////////////////////////////////////
// Input

void AMyProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyProjectCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyProjectCharacter::MoveRight);
	
	//Angles 
	// InputComponent->BindAction("IncreaseCameraAngle", IE_Released, this, &AMyProjectCharacter::IncreaseAngle);
	// InputComponent->BindAction("DecreaseCameraAngle", IE_Released, this, &AMyProjectCharacter::DecreaseAngle);
	//Distance
	//InputComponent->BindAction("IncreaseCameraDistance", IE_Released, this, &AMyProjectCharacter::IncreaseLenght);
	//InputComponent->BindAction("DecreaseCameraDistance", IE_Released, this, &AMyProjectCharacter::DecreaseLenght);
	/***********************************************/
	//Restart
	FInputActionBinding& toggle= InputComponent->BindAction("RestartLevel", IE_Pressed, this, &AMyProjectCharacter::RestartLevel);
	toggle.bExecuteWhenPaused = true;
	//PickUp the items
	InputComponent->BindAction("PutBlock", IE_Pressed, this, &AMyProjectCharacter::PutBlock);

	InputComponent->BindAction("PickUp", IE_Pressed, this, &AMyProjectCharacter::Interact);
	InputComponent->BindAction("FixedCamera", IE_Pressed, this, &AMyProjectCharacter::FixedCamera);

	InputComponent->BindAction("PickUp", IE_Released, this, &AMyProjectCharacter::StopInteract);
	
}

void AMyProjectCharacter::BeginPlay()
{
	Super::BeginPlay();
	//Collision functions
	OnActorHit.AddDynamic(this, &AMyProjectCharacter::OnHit);
	OnActorBeginOverlap.AddDynamic(this, &AMyProjectCharacter::OnOverlap);
	OnActorEndOverlap.AddDynamic(this, &AMyProjectCharacter::EndOverlap);
	//Get world()
	gameMode = GetWorld()->GetAuthGameMode<AMyProjectGameMode>();
	//set camera variables
	CameraBoom->bAbsoluteLocation = isFixedCamera; //Don't want arm to move, is fixed camera
	gameMode->angle = cameraAngle;
	gameMode->distance = cameraLengthToPlayer;	
	
	if (isFixedCamera) 
	{
		CameraBoom->SetRelativeLocation(GetActorLocation());
		CameraBoom->bAbsoluteRotation = true;
	}

}

void AMyProjectCharacter::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	
	if (canPick && canInteract)
	{
		timerCalls += deltaTime;
		if (timerCalls >= timeToCollet)
		{
			Pick();
			timerCalls = 0.0f;
		}
	}
}

void AMyProjectCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMyProjectCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AMyProjectCharacter::IncreaseAngle()
{
	if ((Controller != NULL) && (cameraAngle < -29.0f))
	{
		cameraAngle += 5;
		const FRotator  actualRotation = CameraBoom->GetComponentRotation();
		
		FRotator newRotation = FRotator(cameraAngle, 0, 0);
		//CameraBoom->AddWorldRotation(newRotation);
		CameraBoom->SetWorldRotation(newRotation);
		UE_LOG(LogTemp, Warning, TEXT("%f \n"), actualRotation.Pitch);

		gameMode = GetWorld()->GetAuthGameMode<AMyProjectGameMode>();
		gameMode->angle = cameraAngle;
	}
}

void AMyProjectCharacter::DecreaseAngle()
{
	if ((Controller != NULL) && (cameraAngle > -91.0f))
	{
		cameraAngle -= 5;
		const FRotator  actualRotation = CameraBoom->GetComponentRotation();

		FRotator newRotation = FRotator(cameraAngle, 0, 0);
		//CameraBoom->AddWorldRotation(newRotation);
		CameraBoom->SetWorldRotation(newRotation);
		UE_LOG(LogTemp, Warning, TEXT("%f \n"), actualRotation.Pitch);

		gameMode = GetWorld()->GetAuthGameMode<AMyProjectGameMode>();
		gameMode->angle = cameraAngle;
	}
}

void AMyProjectCharacter::DecreaseLenght()
{
	if ((Controller != NULL) && (cameraLengthToPlayer > 0))
	{
		cameraLengthToPlayer -= 50;
		CameraBoom->TargetArmLength = cameraLengthToPlayer;
	}
}

void AMyProjectCharacter::IncreaseLenght()
{
	if ((Controller != NULL) && (cameraLengthToPlayer < 2500))
	{
		cameraLengthToPlayer += 50;
		CameraBoom->TargetArmLength = cameraLengthToPlayer;
	}
}
void AMyProjectCharacter::FixedCamera()
{
	isFixedCamera = !isFixedCamera;
	CameraBoom->SetRelativeLocation(GetActorLocation());
	
	if (isFixedCamera) 
	{	
		CameraBoom->bAbsoluteLocation = isFixedCamera;
	}
	/*else 
	{
		CameraBoom->bAbsoluteRotation = true;
		CameraBoom->bAbsoluteLocation = false; //Don't want arm to move, is fixed camera
		FollowCamera->bUsePawnControlRotation = false;
	}*/
}

void AMyProjectCharacter::RestartLevel()
{
	gameMode = GetWorld()->GetAuthGameMode<AMyProjectGameMode>();
	if (gameMode->actualGameState != PLAYING) {
		//GetWorld()->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap");
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), true);
	}
}

void AMyProjectCharacter::OnOverlap(AActor * me, AActor * other)
{
	if (Cast<IInteractectable>(other) != nullptr )
	{
		canInteract = true;
		IInteractectable * interacting = Cast<IInteractectable>(other);
		interactObject = interacting;
		interacting = nullptr;
	}
}
void AMyProjectCharacter::EndOverlap(AActor * me, AActor * other)
{
	if (Cast<IInteractectable>(other) != nullptr)
	{
		canInteract = false;
		interactObject = nullptr;
	}
}

void AMyProjectCharacter::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	AEnemyTestCharacter *overalpObject = Cast<AEnemyTestCharacter>(OtherActor);
	if (overalpObject != nullptr) {
		gameMode = GetWorld()->GetAuthGameMode<AMyProjectGameMode>();
		gameMode->actualGameState = LOSE;
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		//gameMode->UpdatePoints(100);
	}
}
void AMyProjectCharacter::Interact() 
{
	
	canPick = true;
	AMyDoor * someDoor = Cast<AMyDoor>(interactObject);

	if (canInteract && (interactObject != nullptr && someDoor != nullptr  ) )
	{
		interactObject->DoPlayerInteraction();
	}
	else if (canInteract && (interactObject != nullptr || someDoor == nullptr))
	{
		canPick = true;
	}

}

void AMyProjectCharacter::PutBlock() 
{
	if (blockToSpawn != nullptr )
	{
		const FRotator actorRotation = GetActorRotation();
		const FVector  actorPosition = GetActorLocation();
		const FVector  forwarVector = GetActorForwardVector() * blockDistanceFromThePlayer;
		FVector  blockTentativePosition = actorPosition + forwarVector;
		blockTentativePosition.Z -= 20;
		const FVector  blockPosition = blockTentativePosition;
		if (currentBlock == nullptr)
		{
			currentBlock = GetWorld()->SpawnActor<ABlock>(blockToSpawn, blockPosition, actorRotation);
			return;
		}
		currentBlock->SetActorLocation(blockPosition);
		currentBlock->SetActorRotation(actorRotation);

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NOT BLOCK"));
	}

}
void AMyProjectCharacter::StopInteract()
{
	canPick = false;
	timerCalls = 0.0f;
}

void AMyProjectCharacter::Pick()
{
	if (canPick && canInteract && interactObject != nullptr)
	{
		interactObject->DoPlayerInteraction();
	}
	
}