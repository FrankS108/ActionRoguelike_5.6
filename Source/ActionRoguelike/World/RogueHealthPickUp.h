// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RoguePickUp.h"
#include "RogueHealthPickUp.generated.h"

UCLASS(Abstract)
class ACTIONROGUELIKE_API ARogueHealthPickUp : public ARoguePickUp
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditDefaultsOnly, Category="PickUp")
	float HealingAmount = 50.0f;
	
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;
	
public:
	// Sets default values for this actor's properties
	ARogueHealthPickUp();
};
