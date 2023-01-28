// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Treasure.h"
#include "Interfaces/Pickup.h"

void ATreasure::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IPickup* PickupInterface = Cast<IPickup>(OtherActor);
	if (PickupInterface)
	{
		PickupInterface->AddGold(this);
		SpawnPickUpSound();
		Destroy();
	}

}
