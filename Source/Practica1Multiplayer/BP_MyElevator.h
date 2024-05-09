// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "BP_MyElevator.generated.h"


class ATargetPoint;

UCLASS()
class PRACTICA1MULTIPLAYER_API ABP_MyElevator : public AActor
{
	GENERATED_BODY()
	
public:	

	ABP_MyElevator();

protected:

	virtual void BeginPlay() override;

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elevator")
	USceneComponent* ElevatorMesh {nullptr};

	UPROPERTY(EditInstanceOnly)
	TArray<ATargetPoint*> Floors = {};

	UFUNCTION()
	void GoToFloor(int32 floor);

	UPROPERTY()
	FVector PosFrom ={};
	
	UPROPERTY()
	FVector PosTo ={};
	
	UPROPERTY()
	bool isMoving = false;
	
	UPROPERTY()
	float Counter =0;
	
	UPROPERTY()
	float Duration = 0;

	UPROPERTY(EditDefaultsOnly)
	float Speed= 200;

	UPROPERTY(EditDefaultsOnly)FRuntimeFloatCurve AnimationCurve;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
