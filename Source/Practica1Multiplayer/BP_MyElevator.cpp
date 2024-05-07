// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_MyElevator.h"

// Sets default values
ABP_MyElevator::ABP_MyElevator()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	//have access to the mesh of the elevator
	ElevatorMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Elevator"));
	ElevatorMesh ->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABP_MyElevator::BeginPlay()
{
	Super::BeginPlay();
	// Initialize elevator position
	ElevatorMesh->SetRelativeLocation(FVector(0, 0, 0));
	
}

// Called every frame
void ABP_MyElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

