// Fill out your copyright notice in the Description page of Project Settings.


#include "ElevatorSwitch.h"
#include <Net/UnrealNetwork.h>
#include "Practica1MultiplayerCharacter.h"

// Sets default values
AElevatorSwitch::AElevatorSwitch()
{
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Root"));
	root->SetupAttachment(RootComponent);
	SetRootComponent(root);


	
	pivot = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Pivot"));
	pivot->SetupAttachment(root);
}


void AElevatorSwitch::BeginPlay()
{
	Super::BeginPlay();

	auto mode = GetNetMode();
	//para que no se haga el tick en servidor
	if(mode == ENetMode::NM_DedicatedServer)
	{
		PrimaryActorTick.bCanEverTick = false;
	}
}


void AElevatorSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

	
}

void AElevatorSwitch::Interact_Implementation()
{
	// IInteractable::Interact_Implementation();
	Press();
}

void AElevatorSwitch::Press()
{
	auto *world = GetWorld();

	if(!world)
		return;


	//
	IsOn = true;
	pivot->SetRelativeLocation(PivotPositionOn);
	
	FTimerHandle handle = {};
	world->GetTimerManager().SetTimer(handle,this, &AElevatorSwitch::Reset,TimePressed,false);

}

void AElevatorSwitch::Reset()
{
	IsOn = false;
	pivot->SetRelativeLocation(PivotPositionOff);
}

void AElevatorSwitch::OnRep_IsOn(bool OldValue)
{

		PrimaryActorTick.bCanEverTick = IsOn;
	UE_LOG(LogTemp, Log, TEXT("IsOn value: {%hs} Old IsOn value: {%hs}"), IsOn ? "true" : "false", OldValue ? "true" : "false");
	
	
}

void AElevatorSwitch::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AElevatorSwitch, IsOn);
}


