// Fill out your copyright notice in the Description page of Project Settings.


#include "Brick.h"
#include "HealthComponent.h"
#include <Components/BoxComponent.h>



// Sets default values
ABrick::ABrick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BRICK"));
	BoxComponent->SetCollisionProfileName(FName("Patatepreset"));
	BoxComponent->SetSimulatePhysics(true);
	BoxComponent->SetNotifyRigidBodyCollision(true);
	RootComponent = BoxComponent;
}

// Called when the game starts or when spawned
void ABrick::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABrick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

