// Fill out your copyright notice in the Description page of Project Settings.


#include "Switch.h"

#include "Components/PointLightComponent.h"

// Sets default values
ASwitch::ASwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Root"));
	root->SetupAttachment(RootComponent);
	SetRootComponent(root);


	
	pivot = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Pivot"));
	pivot->SetupAttachment(root);


	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Lightcmp"));
	Light->SetupAttachment(root);
}

void ASwitch::Toggle()
{
	Multi_Toggle();
}

void ASwitch::Multi_Toggle_Implementation()
{
	IsOn = !IsOn;

	pivot->SetRelativeRotation(IsOn ? PivotRotationOn : PivotRotationOff);
	
	Light->SetIntensity(IsOn ? 5000.f : 0.f);
	Light->SetLightColor(IsOn ? FLinearColor::White : FLinearColor::Black);
}


void ASwitch::Interact_Implementation()
{
	IInteractable::Interact_Implementation();

	Toggle();
}



// Called when the game starts or when spawned
void ASwitch::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

