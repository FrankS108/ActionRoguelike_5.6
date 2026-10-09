// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RogueActionSystemComponent.generated.h"

USTRUCT(BlueprintType)
struct FRogueAttributeSet
{
	GENERATED_BODY()
	
	FRogueAttributeSet()
		: Health(100.0f){}
	
	UPROPERTY(BlueprintReadOnly)
	float Health;
	
	UPROPERTY(BlueprintReadOnly)
	float HealthMax = 100.0f;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, OldHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChanged, FName, Attribute, float, NewValue, float, OldValue);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API URogueActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	void ApplyHealthChange(float InValueChange);
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
	
protected:
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FRogueAttributeSet Attributes;

public:
	
	URogueActionSystemComponent();
	
	bool IsFullHealth() const;

};
