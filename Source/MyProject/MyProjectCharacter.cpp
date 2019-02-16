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
#include "EnemyTestCharacter.h"
#include "Point.h"
#include "PlayerCameraShake.h"
#include "Engine/World.h"
#include "MyProjectGameMode.h"
#include "Kismet/GameplayStatics.h"

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
	canPickUp = false;
	//Set the camera debug variables
	isFixedCamera = false;
	cameraAngle = -90.0f;
	cameraLengthToPlayer = 1500.0f;

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
	InputComponent->BindAction("IncreaseCameraAngle", IE_Released, this, &AMyProjectCharacter::IncreaseAngle);
	InputComponent->BindAction("DecreaseCameraAngle", IE_Released, this, &AMyProjectCharacter::DecreaseAngle);
	//Distance
	InputComponent->BindAction("IncreaseCameraDistance", IE_Released, this, &AMyProjectCharacter::IncreaseLenght);
	InputComponent->BindAction("DecreaseCameraDistance", IE_Released, this, &AMyProjectCharacter::DecreaseLenght);
	//Restart
	FInputActionBinding& toggle= InputComponent->BindAction("RestartLevel", IE_Pressed, this, &AMyProjectCharacter::RestartLevel);
	toggle.bExecuteWhenPaused = true;
	//PickUp the items
	InputComponent->BindAction("PickUp", IE_Pressed, this, &AMyProjectCharacter::PickUp);
	
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
}

void AMyProjectCharacter::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	if (onPause) {
		/*currTime += deltaTime;
		UE_LOG(LogTemp, Warning, TEXT("%f \n"), currTime);*/
		if (GetWorld() != nullptr) {
			UGameplayStatics::SetGamePaused(GetWorld(), onPause);
		}
	}
		
	if (gameMode->gameState != PLAYING && onPause == false) {
		onPause = true;
		UGameplayStatics::SetGamePaused(GetWorld(), onPause);
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

		gameMode = GetWorld()->GetAuthGameMode<AMyProjectGameMode>();
		gameMode->distance = cameraLengthToPlayer;
	}
}

void AMyProjectCharacter::IncreaseLenght()
{
	if ((Controller != NULL) && (cameraLengthToPlayer < 2500))
	{
		cameraLengthToPlayer += 50;
		CameraBoom->TargetArmLength = cameraLengthToPlayer;
	
		gameMode = GetWorld()->GetAuthGameMode<AMyProjectGameMode>();
		gameMode->distance = cameraLengthToPlayer;
	}
}

void AMyProjectCharacter::RestartLevel()
{
	gameMode = GetWorld()->GetAuthGameMode<AMyProjectGameMode>();
	if (gameMode->gameState != PLAYING) {
		GetWorld()->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap");				
	}

	//set pause end		
	if (onPause == true) {
		UGameplayStatics::SetGamePaused(GetWorld(),false);
		onPause = false;
	}
}

void AMyProjectCharacter::OnOverlap(AActor * me, AActor * other)
{
	if (Cast<APoint>(other) != nullptr ) {
		canPickUp = true;
		APoint *point = Cast<APoint>(other);
		pickPoint = point;
		if (myShake != NULL) {
			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(myShake,1.0f);
		}
	}
}
void AMyProjectCharacter::EndOverlap(AActor * me, AActor * other)
{
	if (Cast<APoint>(other) != nullptr) {
		canPickUp = false;
		APoint *point = nullptr;
	}
}

void AMyProjectCharacter::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	AEnemyTestCharacter *overalpObject = Cast<AEnemyTestCharacter>(OtherActor);
	if (overalpObject != nullptr) {
		gameMode = GetWorld()->GetAuthGameMode<AMyProjectGameMode>();
		gameMode->gameState = LOSE;
		gameMode->UpdatePoints(100);
	}
}
void AMyProjectCharacter::PickUp() {
	if (canPickUp && pickPoint != nullptr){
		gameMode->UpdateScore(pickPoint->points);
		gameMode->UpdatePoints(-1);
		pickPoint->Destroy();
		canPickUp = false;
	}
}