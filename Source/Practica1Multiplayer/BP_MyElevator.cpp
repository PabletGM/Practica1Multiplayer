// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_MyElevator.h"

#include "ElevatorSwitch.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "Logging/StructuredLog.h"

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
	// ElevatorMesh->SetRelativeLocation(FVector(0, 0, 0));

	//para que el elevador se pueda suscribir a todos los eventos.
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AElevatorSwitch::StaticClass(),FoundActors);

	//para cada actor de AElevatorSwitch, && es muy util, pilla todas las referencias
	for(auto * actor: FoundActors)
	{
		if(auto * eSwitch = Cast<AElevatorSwitch>(actor))
		{
			//comprobamos si NO esta suscrito a la funcion GoToFloor
			if(!eSwitch->OnElevatorSwitchPressed.IsAlreadyBound(this, &ABP_MyElevator::GoToFloor))
			{
				//lo suscribimos a OnElevatorSwitchPressed el metodo GoToFloor para que llegue a la funcion GoToFloor
				//el numero de la planta a la que queremos ir
				eSwitch->OnElevatorSwitchPressed.AddDynamic(this,&ABP_MyElevator::GoToFloor);
			}
			
		}

	}
}

void ABP_MyElevator::GoToFloor(int32 floor)
{
	UE_LOGFMT(LogTemp, Log, "Go to floor: {0}", floor);
	
	//mira si existe la planta en la que estamos
	if(!Floors.IsValidIndex(floor))
	{
		return;
	}
	//cogemos el objeto target targetPoint
	auto * target = Floors[floor];
	
	//ponemos a el elevator la posicion del targetPoint
	SetActorLocation(target->GetActorLocation());
}

// Called every frame
void ABP_MyElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

