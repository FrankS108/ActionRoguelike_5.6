// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueProjectile_Blackhole.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"


// Sets default values
ARogueProjectile_Blackhole::ARogueProjectile_Blackhole()
{
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComponent->SetupAttachment(RootComponent);
	RadialForceComponent->ForceStrength = -8000000;
	RadialForceComponent->Radius = 1200.0f;
	RadialForceComponent->RemoveObjectTypeToAffect(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	
	SphereComponent->SetSphereRadius(20.0f);
	SphereComponent->SetCollisionProfileName("BlackholeCore");
	
	ProjectileMovementComponent->InitialSpeed = 500.0f;
}

void ARogueProjectile_Blackhole::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnSphereBeginOverlap);
}

void ARogueProjectile_Blackhole::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &ThisClass::DestroyBlackHole, DelayTimeDestroy, false);
}

void ARogueProjectile_Blackhole::DestroyBlackHole()
{
	Destroy();
}

void ARogueProjectile_Blackhole::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->IsSimulatingPhysics())
	{
		OtherActor->Destroy();
	}
}






