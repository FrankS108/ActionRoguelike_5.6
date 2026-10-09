// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueExplosiveBarrel.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"


// Sets default values
ARogueExplosiveBarrel::ARogueExplosiveBarrel()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComponent->SetSimulatePhysics(true);
	SetRootComponent(MeshComponent);
	
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComponent->SetupAttachment(MeshComponent);
	RadialForceComponent->ForceStrength = 2000.0f;
	RadialForceComponent->Radius = 200.0f;
	
	RadialForceComponent->bAutoActivate = false;
	RadialForceComponent->bIgnoreOwningActor = true;
	
	
	bCanExplode = true;
}

float ARogueExplosiveBarrel::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (!bCanExplode || GetWorld()->GetTimerManager().IsTimerActive(ExplodeTimerHandle))
	{
		return ActualDamage;
	}
	
	LoopedFlamesComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(FlamesNiagaraSystem, MeshComponent, NAME_None, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::Type::SnapToTarget, true);
	LoopedFlamesAudioComponent = UGameplayStatics::SpawnSoundAttached(FlamesSound, MeshComponent);
	GetWorld()->GetTimerManager().SetTimer(ExplodeTimerHandle, this, &ThisClass::Explode, DelayTimeExplode);
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ARogueExplosiveBarrel::Explode()
{
	bCanExplode = false;
	
	if (LoopedFlamesAudioComponent && LoopedFlamesAudioComponent->IsPlaying())
	{
		LoopedFlamesAudioComponent->Stop();
	}

	if (LoopedFlamesComponent)
	{
		LoopedFlamesComponent->Deactivate();
	}
	MeshComponent->AddImpulse(FVector::UpVector * 1000, NAME_None, true);
	MeshComponent->AddAngularImpulseInDegrees(FVector::RightVector * 1000, NAME_None, true);
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionNiagaraSystem, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());
	RadialForceComponent->FireImpulse();
}


