// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "TimerManager.h"
#include <DrawDebugHelpers.h>
#include <Kismet/KismetMathLibrary.h> 
#include <Kismet/Gameplaystatics.h> 
#include "Engine/World.h"
#include <GameFramework/ProjectileMovementComponent.h>



// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SightSource = CreateDefaultSubobject<USceneComponent>(TEXT("Sight Source"));
	SightSource->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	bCanSeePlayer = LookAtActor(PlayerCharacter);

	if (bCanSeePlayer != bPreviousCanSeePlayer) {

		if (bCanSeePlayer) {
			//start timer
			GetWorldTimerManager().SetTimer(ThrowTimerHandle,this,&AEnemy::ThrowPatate,ThrowingInterval,true,ThrowingDelay);

		}
		else {
			//stop timer		
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::White, TEXT("Patate"));
			GetWorldTimerManager().ClearTimer(ThrowTimerHandle);
		}
	}		
	bPreviousCanSeePlayer = bCanSeePlayer;


}

void AEnemy::ThrowPatate() {
	if (PatateClass == nullptr) {
		return;
	}
	FVector ForwardVector = GetActorForwardVector();
	float SpawnDistance = 40.f;
	FVector SpawnLocation = GetActorLocation() + (ForwardVector * SpawnDistance);
	FTransform SpawnTransform(GetActorRotation(),SpawnLocation);

	APatate* Patate = GetWorld()->SpawnActorDeferred<APatate>(PatateClass,SpawnTransform);
	Patate->GetProjectileMovementComponent()->InitialSpeed = 2200.f;
	Patate->FinishSpawning(SpawnTransform);




	//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::White, TEXT("Patate!!"));
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


bool AEnemy::LookAtActor(AActor* Target) {
	if (CanSee(Target)) {
		FVector Start = GetActorLocation();
		FVector End = Target->GetActorLocation();
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Start, End);
		LookAtRotation.Pitch = 0;
		LookAtRotation.Roll = 0;
		SetActorRotation(LookAtRotation);
		return true;
	}
	return false;
}

bool AEnemy::CanSee(const AActor* Target)
{
	if (Target == nullptr) return false;
	FHitResult Hit;

	FVector Start = SightSource->GetComponentLocation();
	FVector End = Target->GetActorLocation();

	FCollisionQueryParams QueryParam;
	QueryParam.AddIgnoredActor(this);
	QueryParam.AddIgnoredActor(Target);

	ECollisionChannel Channel = ECollisionChannel::ECC_Visibility;
	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, Channel);

	if (!Hit.bBlockingHit) DrawDebugLine(GetWorld(), Start, End, FColor::Red);

	return !Hit.bBlockingHit;
}

