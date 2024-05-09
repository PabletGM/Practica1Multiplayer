
#include "ElevatorSwitch.h"
#include <Net/UnrealNetwork.h>
#include "Practica1MultiplayerCharacter.h"


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
}


void AElevatorSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(IsOn)
	{
		//timer
		Counter+=DeltaTime;
		const auto value = Counter/TimePressed;
		//curve value
		const auto eval = AnimationCurve.ExternalCurve
			? AnimationCurve.ExternalCurve->GetFloatValue(value)
			: AnimationCurve.EditorCurveData.Eval(value);

		//position of value
		const auto pos = FMath::Lerp(PivotPositionOff,PivotPositionOn, eval);
		pivot ->SetRelativeLocation(pos);
	}
}

void AElevatorSwitch::Interact_Implementation()
{
	Press();
}

void AElevatorSwitch::Press()
{
	if(IsOn)
		return;
	
	auto *world = GetWorld();
	
	if(!world)
		return;
	
	IsOn = true;
	//suscribe to delegate the param TargetFloor
	OnElevatorSwitchPressed.Broadcast(TargetFloor);
	//timer to call Reset
	FTimerHandle handle = {};
	world->GetTimerManager().SetTimer(handle,this, &AElevatorSwitch::Reset,TimePressed,false);
}

void AElevatorSwitch::Reset()
{
	IsOn = false;
	Counter=0.f;
}

void AElevatorSwitch::OnRep_IsOn(bool OldValue)
{
	if(!IsOn)
	{
		Reset();
	}
}

void AElevatorSwitch::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AElevatorSwitch, IsOn);
}