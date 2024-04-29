// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_PickUpComponent.h"

UTP_PickUpComponent::UTP_PickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void UTP_PickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UTP_PickUpComponent::OnSphereBeginOverlap);
}

void UTP_PickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	APractica1MultiplayerCharacter* Character = Cast<APractica1MultiplayerCharacter>(OtherActor);
	if(Character != nullptr)
	{
		if(auto *owner =GetOwner())
		{
			//auto  mode = owner->GetNetMode();
			auto  roleLoc = owner->GetLocalRole();
			//auto  roleRem = owner->GetRemoteRole();
			if(roleLoc == ENetRole::ROLE_Authority)
			{
				owner->SetOwner(Character);
			}
			// if(roleLoc == ENetMode::)
		}
			
		
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
