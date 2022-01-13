// Fill out your copyright notice in the Description page of Project Settings.


#include "Patate.h"
#include "MyProjectCharacter.h"

#include <Components/SphereComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <MyProject/Brick.h>
#include <MyProject/HealthComponent.h>

// Sets default values
APatate::APatate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("PATATE"));
	SphereComponent->SetSphereRadius(20.f);
	SphereComponent->SetCollisionProfileName(FName("Patatepreset"));
	SphereComponent->SetSimulatePhysics(true);
	SphereComponent->SetNotifyRigidBodyCollision(true);
	SphereComponent->OnComponentHit.AddDynamic(this, &APatate::OnHit);
	RootComponent = SphereComponent;
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));



}

void APatate::OnHit(UPrimitiveComponent* Hitcomp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ABrick *brickActor = Cast<ABrick>(OtherActor);
	if (brickActor != nullptr) {
		(brickActor->GetHealthComponent())->LoseHealth(10.f);
	}
}

// Called when the game starts or when spawned
void APatate::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentHit.AddDynamic(this, &APatate::OnHit);

}

// Called every frame
void APatate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

