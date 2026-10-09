// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueProjectile.h"
#include "RogueProjectile_Teleport.generated.h"

class UNiagaraSystem;
class USoundBase;

UCLASS()
class ACTIONROGUELIKE_API ARogueProjectile_Teleport : public ARogueProjectile
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="Components")
	float AutoTeleportDelay;
	
	UPROPERTY(EditDefaultsOnly, Category="Components")
	float TeleportDelay;
	
	UPROPERTY(EditDefaultsOnly, Category="Damage")
	TSubclassOf<UDamageType> DamageType;
	
	FTimerHandle TeleportTimerHandle;
	
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );
	
	void StartDelayedTeleport();
	
	void HandleTeleportation();

public:
	
	virtual void PostInitializeComponents() override;
	
	ARogueProjectile_Teleport();

};
