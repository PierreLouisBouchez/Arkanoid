// Fill out your copyright notice in the Description page of Project Settings.


#include "BrickGrid.h"

// Sets default values
ABrickGrid::ABrickGrid()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABrickGrid::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABrickGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABrickGrid::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

