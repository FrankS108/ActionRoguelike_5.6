// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueProjectile_Teleport.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ARogueProjectile_Teleport::ARogueProjectile_Teleport()
{

}

void ARogueProjectile_Teleport::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	SphereComponent->OnComponentHit.AddDynamic(this, &ThisClass::OnActorHit);
	SphereComponent->IgnoreActorWhenMoving(GetInstigator(), true);
}

void ARogueProjectile_Teleport::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(TeleportTimerHandle, this, &ThisClass::StartDelayedTeleport, AutoTeleportDelay, false);
}

void ARogueProjectile_Teleport::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                           UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GetWorldTimerManager().ClearTimer(TeleportTimerHandle);
	
	StartDelayedTeleport();
}

void ARogueProjectile_Teleport::StartDelayedTeleport()
{
	PlayExplodeEffects();
	
	ProjectileMovementComponent->StopMovementImmediately();
	
	if (LoopedNiagaraComponent)
	{
		LoopedNiagaraComponent->Deactivate();	
	}

	if (LoopedAudioComponent)
	{
		LoopedAudioComponent->Stop();	
	}
	
	SetActorEnableCollision(false);
	
	GetWorldTimerManager().SetTimer(TeleportTimerHandle, this, &ThisClass::HandleTeleportation, TeleportDelay);
}

void ARogueProjectile_Teleport::HandleTeleportation()
{
	APawn* InstigatorToTeleport = GetInstigator();
	
	InstigatorToTeleport->TeleportTo(GetActorLocation(), InstigatorToTeleport->GetActorRotation());
	
	Destroy();
}
