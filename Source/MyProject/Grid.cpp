// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"
#include "Brick.h"


// Sets default values
AGrid::AGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGrid::BeginPlay()
{
	if (BrickClass == nullptr) {
		return;
	}
	Super::BeginPlay();

	for (int i = 0; i < 14; ++i) {

		for (int j = 1; j < 11; ++j) {

			FRotator ForwardVector(0.f, 0.f, 0.f);
			FVector SpawnLocation(j*75.f,  i* 200.f -1300.f, 200);
			FTransform SpawnTransform(ForwardVector, SpawnLocation);

			ABrick* Brick = GetWorld()->SpawnActorDeferred<ABrick>(BrickClass, SpawnTransform);
			Brick->FinishSpawning(SpawnTransform);
		}
	}
}


// Called every frame
void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

