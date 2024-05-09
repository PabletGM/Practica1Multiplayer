// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_MyElevator.h"
#include "ElevatorSwitch.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABP_MyElevator::ABP_MyElevator()
{
	PrimaryActorTick.bCanEverTick = true;
	//have access to the mesh of the elevator
	ElevatorMesh = CreateDefaultSubobject<USceneComponent>(TEXT("Elevator"));
	ElevatorMesh ->SetupAttachment(RootComponent);
}

void ABP_MyElevator::BeginPlay()
{
	Super::BeginPlay();
	//for the elevator suscribing to all the methods.
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AElevatorSwitch::StaticClass(),FoundActors);
	
	for(auto * actor: FoundActors)
	{
		if(auto * eSwitch = Cast<AElevatorSwitch>(actor))
		{
			//check if it is not suscribed to function GoToFloor
			if(!eSwitch->OnElevatorSwitchPressed.IsAlreadyBound(this, &ABP_MyElevator::GoToFloor))
			{
				//suscribe the method GoToFloor to the delegate
				eSwitch->OnElevatorSwitchPressed.AddDynamic(this,&ABP_MyElevator::GoToFloor);
			}
		}
	}
}

void ABP_MyElevator::GoToFloor(int32 floor)
{
	if(isMoving)
		return;
	//does it exist the floor?
	if(!Floors.IsValidIndex(floor))
		return;
	//take the object targetPoint
    auto * target = Floors[floor];
	//where it comes
	PosFrom = GetActorLocation();
	//where it goes
	PosTo= target->GetActorLocation();
	//reboot counter
	Counter =0.f;
	// duration = t = length /speed
	Duration = (PosTo - PosFrom).Length() /Speed;
	isMoving = true;
}

void ABP_MyElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(isMoving)
	{
		//timer
		Counter+=DeltaTime;
		//value changing by duration
		 auto value = Counter/Duration;
		//end of move?
		if(value > 1.f)
		{
			value = 1.f;
			isMoving = false;
		}
		//animation curve
		const auto eval = AnimationCurve.ExternalCurve
			? AnimationCurve.ExternalCurve->GetFloatValue(value)
			: AnimationCurve.EditorCurveData.Eval(value);
		//position
		const auto pos = FMath::Lerp(PosFrom,PosTo, eval);
		SetActorLocation(pos);
	}
}