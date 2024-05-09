// Copyright Epic Games, Inc. All Rights Reserved.

#include "Practica1MultiplayerCharacter.h"
#include "Practica1MultiplayerProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "TP_WeaponComponent.h"
#include "Engine/LocalPlayer.h"
#include <Net/UnrealNetwork.h>

#include "Switch.h"
#include "Kismet/KismetSystemLibrary.h"


DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// APractica1MultiplayerCharacter

APractica1MultiplayerCharacter::APractica1MultiplayerCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

}

void APractica1MultiplayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APractica1MultiplayerCharacter, Weapon);
}


void APractica1MultiplayerCharacter::Server_Fire_Implementation()
{
	auto mode = GetNetMode();
	if(!Weapon)
		return;
	
	UE_LOG(LogTemp, Log, TEXT("%i"), mode);
	Weapon->Fire_SpawnBall();
	
	Multi_Fire();
}

void APractica1MultiplayerCharacter::Multi_Fire_Implementation()
{
	if(!Weapon)
	{
		return;
	}
	auto role = GetLocalRole();

	//solo lo hace los clientes
	if(role == ENetRole::ROLE_AutonomousProxy || role == ENetRole::ROLE_SimulatedProxy)
	{
		Weapon->Fire_Animation();
		Weapon->Fire_Sound();
	}
}





void APractica1MultiplayerCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}

//////////////////////////////////////////////////////////////////////////// Input

void APractica1MultiplayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APractica1MultiplayerCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APractica1MultiplayerCharacter::Look);

		// iNTERACT
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &APractica1MultiplayerCharacter::Interact);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void APractica1MultiplayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void APractica1MultiplayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APractica1MultiplayerCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool APractica1MultiplayerCharacter::GetHasRifle()
{
	return bHasRifle;
}

void APractica1MultiplayerCharacter::Interact()
{
	UE_LOG(LogTemp, Log, TEXT("H"));

	const auto start = FirstPersonCameraComponent->GetComponentLocation();
	const auto end = start +FirstPersonCameraComponent->GetForwardVector() * 100.f;

	auto hit = FHitResult();
	UKismetSystemLibrary::SphereTraceSingle(this,start, end,20.f, TraceTypeQuery1, false,{},EDrawDebugTrace::ForDuration, hit,true,FLinearColor::Red, FLinearColor::Green, 5.f);

	if(auto* actor = hit.GetActor())
	{
		if(auto* interface = Cast<IInteractable>(actor))
		{
			if(UKismetSystemLibrary::DoesImplementInterface(actor,UInteractable::StaticClass()))
			{
				Server_Interact(actor);
			}
		}
	}
}

void APractica1MultiplayerCharacter::Server_Interact_Implementation(AActor* actor)
{
	if(!actor)
	{
		return;
	}

	IInteractable::Execute_Interact(actor);
}


