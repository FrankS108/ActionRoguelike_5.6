// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueProjectileMagic.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARogueProjectileMagic::ARogueProjectileMagic()
{
	
}

void ARogueProjectileMagic::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	SphereComponent->OnComponentHit.AddDynamic(this, &ThisClass::OnActorHit);
	SphereComponent->IgnoreActorWhenMoving(GetInstigator(), true);
}

void ARogueProjectileMagic::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit )
{
	FVector HitFromDirection = GetActorRotation().Vector();
	
	UGameplayStatics::ApplyPointDamage(OtherActor, 10.0f, HitFromDirection, Hit, GetInstigatorController(), this, DamageType);
	
	PlayExplodeEffects();
	
	Destroy();
}


