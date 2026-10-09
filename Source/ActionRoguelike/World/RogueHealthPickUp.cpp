// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueHealthPickUp.h"

#include "ActionSystem/RogueActionSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/RoguePlayerCharacter.h"


// Sets default values
ARogueHealthPickUp::ARogueHealthPickUp()
{
	SphereComponent->SetCollisionProfileName(TEXT("PickUp"));
	MeshComponent->SetCollisionProfileName("NoCollision");
}


void ARogueHealthPickUp::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	URogueActionSystemComponent* ActionSystemComponent = OtherActor->FindComponentByClass<URogueActionSystemComponent>();
		
	if (IsValid(ActionSystemComponent))
	{
		if (!ActionSystemComponent->IsFullHealth())
		{
			ActionSystemComponent->ApplyHealthChange(HealingAmount);
			UGameplayStatics::PlaySoundAtLocation(this, SoundPickUp, GetActorLocation());
			Destroy();
		}
	}
	
}


