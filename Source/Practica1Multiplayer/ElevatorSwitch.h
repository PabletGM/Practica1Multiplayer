// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "ElevatorSwitch.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnElevatorSwitchPressed,int, floor);

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

	//it calls function OnRep_IsOn when replicates
	UPROPERTY(ReplicatedUsing=OnRep_IsOn)
	bool IsOn = false;

	UPROPERTY(EditDefaultsOnly)
	float TimePressed = 1.f;

	float Counter = 0.f;

	UPROPERTY(EditInstanceOnly)
	int TargetFloor= 0;

	UPROPERTY(EditDefaultsOnly)FRuntimeFloatCurve AnimationCurve;
	
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

	UPROPERTY(BlueprintAssignable)
	FOnElevatorSwitchPressed OnElevatorSwitchPressed = {};

};
