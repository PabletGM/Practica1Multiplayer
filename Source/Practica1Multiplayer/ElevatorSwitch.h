// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "ElevatorSwitch.generated.h"

UCLASS()
class PRACTICA1MULTIPLAYER_API AElevatorSwitch : public AActor, public IInteractable
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	USceneComponent *pivot = nullptr;

	UPROPERTY(EditAnywhere)
	USceneComponent *root= nullptr;

	UPROPERTY(EditDefaultsOnly)
	FVector PivotPositionOn= {};

	UPROPERTY(EditDefaultsOnly)
	FVector PivotPositionOff= {};

	//se llama a funcion al replicar el IsoN
	UPROPERTY(ReplicatedUsing=OnRep_IsOn)
	bool IsOn = false;

	UPROPERTY(EditDefaultsOnly)
	float TimePressed = 1.f;

	float Counter = 0.f;
	
public:	

	AElevatorSwitch();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation() override;

	void Press();
	void Reset();

	UFUNCTION()
	void OnRep_IsOn(bool OldValue);

};
