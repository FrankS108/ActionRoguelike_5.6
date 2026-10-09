// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueProjectile.h"
#include "RogueProjectile_Blackhole.generated.h"

class URadialForceComponent;
class UNiagaraSystem;


UCLASS(Abstract)
class ACTIONROGUELIKE_API ARogueProjectile_Blackhole : public ARogueProjectile
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category="Components")
	float DelayTimeDestroy;
	
	UPROPERTY(EditDefaultsOnly, Category="Damage")
	TSubclassOf<UDamageType> DamageType;
	
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<URadialForceComponent> RadialForceComponent;
	
	FTimerHandle DestroyTimerHandle;
	
	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	virtual void BeginPlay() override;
	
	void DestroyBlackHole();

public:
	
	virtual void PostInitializeComponents() override;
	
	ARogueProjectile_Blackhole();

};
