// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "Switch.generated.h"

class UPointLightComponent;

UCLASS()
class PRACTICA1MULTIPLAYER_API ASwitch : public AActor, public IInteractable
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	USceneComponent *pivot = nullptr;

	UPROPERTY(EditAnywhere)
	USceneComponent *root= nullptr;

	UPROPERTY(EditDefaultsOnly)
	FRotator PivotRotationOn= {};

	UPROPERTY(EditDefaultsOnly)
	FRotator PivotRotationOff= {};

	UPROPERTY(EditDefaultsOnly)
	UPointLightComponent *Light= nullptr;
	
public:	
	ASwitch();

	UPROPERTY(BlueprintReadWrite)
	bool IsOn = false;

	UFUNCTION(BlueprintCallable)
	void Toggle();

	UFUNCTION(NetMulticast, Reliable)
	void Multi_Toggle();

	virtual void Interact_Implementation() override;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};
