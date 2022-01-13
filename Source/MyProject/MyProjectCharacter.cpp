// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProjectCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include <GameFramework/ProjectileMovementComponent.h>


//////////////////////////////////////////////////////////////////////////
// AMyProjectCharacter

AMyProjectCharacter::AMyProjectCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	//GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->AirControl = 5.f;
	GetCharacterMovement()->MaxWalkSpeed = 1200.f;
	GetCharacterMovement()->MaxAcceleration = 1500.f;


	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 700.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm


	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritRoll = false;
	CameraBoom->bInheritYaw = false;
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
	FRotator ForwardVector(1.f, 0.f, 0.f);
	float SpawnDistance = 40.f;
	FVector SpawnLocation = GetActorLocation();
	SpawnLocation.X += SpawnDistance;
	FTransform SpawnTransform(ForwardVector, SpawnLocation);

	//Balle = GetWorld()->SpawnActorDeferred<APatate>(PatateClass, SpawnTransform);
	//Balle->GetProjectileMovementComponent()->InitialSpeed = 800.f;
	//Balle->GetProjectileMovementComponent()->MaxSpeed = 800.f;

	//Balle->FinishSpawning(SpawnTransform);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMyProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AMyProjectCharacter::ThrowPatate);

	PlayerInputComponent->BindAxis("MoveRight", this, &AMyProjectCharacter::MoveRight);


	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AMyProjectCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AMyProjectCharacter::TouchStopped);
}



void AMyProjectCharacter::ThrowPatate() {

	if (PatateClass == nullptr || launch) {
		return;
	}
	FRotator ForwardVector(1.f,0.f,0.f);
	float SpawnDistance = 40.f;
	FVector SpawnLocation = GetActorLocation();
	SpawnLocation.X+=SpawnDistance;
	FTransform SpawnTransform(ForwardVector,SpawnLocation);

	APatate* Patate = GetWorld()->SpawnActorDeferred<APatate>(PatateClass, SpawnTransform);
	Patate->GetProjectileMovementComponent()->InitialSpeed = 800.f;
	Patate->GetProjectileMovementComponent()->MaxSpeed = 800.f;

	Patate->FinishSpawning(SpawnTransform);
	launch = true;
}

void AMyProjectCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	ThrowPatate();	
}

void AMyProjectCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AMyProjectCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		const FVector Direction(0,1,0);
		AddMovementInput(Direction, Value);
	}
}
