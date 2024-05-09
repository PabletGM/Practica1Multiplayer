
#include "Switch.h"
#include "Components/PointLightComponent.h"

ASwitch::ASwitch()
{
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
	//depending of the value change rotation and intensity and color
	pivot->SetRelativeRotation(IsOn ? PivotRotationOn : PivotRotationOff);
	Light->SetIntensity(IsOn ? 5000.f : 0.f);
	Light->SetLightColor(IsOn ? FLinearColor::White : FLinearColor::Black);
}

void ASwitch::Interact_Implementation()
{
	IInteractable::Interact_Implementation();
	Toggle();
}

void ASwitch::BeginPlay()
{
	Super::BeginPlay();
}

void ASwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}