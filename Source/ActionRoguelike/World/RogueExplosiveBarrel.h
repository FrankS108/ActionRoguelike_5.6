// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogueExplosiveBarrel.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;
class USoundBase;
class UAudioComponent;
class UStaticMeshComponent;
class URadialForceComponent;
UCLASS(Abstract)
class ACTIONROGUELIKE_API ARogueExplosiveBarrel : public AActor
{
	GENERATED_BODY()

public:
	ARogueExplosiveBarrel();

protected:
	
	UPROPERTY(EditDefaultsOnly, Category="Components")
	float DelayTimeExplode;
	
	UPROPERTY(EditDefaultsOnly, Category="Componentss")
	TObjectPtr<UStaticMeshComponent> MeshComp;
	
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<URadialForceComponent> RadialForceComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<UNiagaraSystem> FlamesNiagaraSystem;

	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<UNiagaraSystem> ExplosionNiagaraSystem;
	
	UPROPERTY(EditDefaultsOnly, Category="Sound")
	TObjectPtr<USoundBase> FlamesSound;
	
	UPROPERTY(EditDefaultsOnly, Category="Sound")
	TObjectPtr<USoundBase> ExplosionSound;
	
	UPROPERTY()
	TObjectPtr<UNiagaraComponent> LoopedFlamesComponent;
	
	UPROPERTY()
	TObjectPtr<UAudioComponent> LoopedFlamesAudioComponent;
	
	uint8 bCanExplode : 1;
	
	FTimerHandle ExplodeTimerHandle;
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	void Explode();

};
