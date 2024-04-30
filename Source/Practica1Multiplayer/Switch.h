// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Switch.generated.h"

UCLASS()
class PRACTICA1MULTIPLAYER_API ASwitch : public AActor
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
	
public:	
	// Sets default values for this actor's properties
	ASwitch();

	UPROPERTY(BlueprintReadWrite)
	bool IsOn = false;

	UFUNCTION(BlueprintCallable)
	void Toggle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
