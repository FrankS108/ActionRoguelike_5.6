// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueInteractionComponent.h"

#include "RogueGameTypes.h"
#include "Core/RogueInteractionInterface.h"
#include "Engine/OverlapResult.h"


TAutoConsoleVariable<bool> CVarInteractionDebugDrawing(
	TEXT("game.interaction.DebugDraw"), 
	false, 
	TEXT("Enable interaction component debug rendering"), 
	ECVF_Cheat
	);

// Sets default values for this component's properties
URogueInteractionComponent::URogueInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void URogueInteractionComponent::Interact()
{
	if (SelectedActor)
	{
		IRogueInteractionInterface::Execute_Interact(SelectedActor);	
	}
}

// Called every frame
void URogueInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	APlayerController* PC = CastChecked<APlayerController>(GetOwner());
	
	FVector Center = PC->GetPawn()->GetActorLocation();
	FVector CameraLocation = PC->PlayerCameraManager->GetCameraLocation();
	
	//DrawDebugBox(GetWorld(), Center, FVector(20.0f), FColor::Red);
	
	ECollisionChannel CollisionChannel = COLLISION_INTERACTION;
	
	FCollisionShape Shape;
	Shape.SetSphere(InteractionRadius);
	
	float InteractionRadiusSqrd = (InteractionRadius * InteractionRadius);
	
	TArray<FOverlapResult> Overlaps;
	GetWorld()->OverlapMultiByChannel(Overlaps, Center, FQuat::Identity, CollisionChannel, Shape);
	
	AActor* BestActor = nullptr;
	float HighestWeight = 0.0f;
	
	bool bEnableDebugDraw = CVarInteractionDebugDrawing.GetValueOnGameThread();
	
	for (FOverlapResult& Overlap : Overlaps)
	{
		FVector Origin;
		FVector BoxExtends;
		Overlap.GetActor()->GetActorBounds(true, Origin, BoxExtends);
		
		//FVector OverlapLocation = Overlap.GetActor()->GetActorLocation();
		
		FVector OverlapDirection = (Origin - CameraLocation).GetSafeNormal();
		
		float DistanceToSqrd = (Origin - Center).SizeSquared();
		
		//Normalize and invert, smaller dist is higher weight
		float NormalizedDistanceTo = 1.0f - (DistanceToSqrd / InteractionRadiusSqrd);
		
		float DotResult = FVector::DotProduct(OverlapDirection, PC->GetControlRotation().Vector());
		
		//Normalize 0.0f - 1.0f
		float NormalizedDotResult = DotResult * 0.5 + 0.5;
		
		float Weight = (NormalizedDotResult * DirectionWeightScale) + (NormalizedDistanceTo * DistanceToWeightScale);
		if (Weight > HighestWeight)
		{
			BestActor = Overlap.GetActor();
			HighestWeight = Weight;
		}

		if (bEnableDebugDraw)
		{
			DrawDebugBox(GetWorld(), Origin, FVector(50.0f), FColor::Red);
			FString DebugString = FString::Printf(TEXT("Wight: %f, Dot: %f, Dist: %f"), Weight, NormalizedDotResult, NormalizedDistanceTo);
			DrawDebugString(GetWorld(), Origin, DebugString, nullptr, FColor::White, 0.0f, true);
		}
	}
	
	SelectedActor = BestActor;

	if (bEnableDebugDraw)
	{
		if (BestActor)
		{
			DrawDebugBox(GetWorld(), BestActor->GetActorLocation(), FVector(60.0f), FColor::Green);
		}
		
		DrawDebugSphere(GetWorld(), Center, InteractionRadius, 32.0f, FColor::White);
	}
	
	

}

