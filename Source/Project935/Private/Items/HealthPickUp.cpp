// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/HealthPickUp.h"
#include "Interfaces/Pickup.h"
#include "Characters/BaseCharacter.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"



AHealthPickUp::AHealthPickUp()
{
	HeartColors.Add(FLinearColor(1.f, 0.f, 0.f, 1.f));
	HeartColors.Add(FLinearColor(0.f, 1.f, 0.f, 1.f));
	HeartColors.Add(FLinearColor(0.f, 0.f, 1.f, 1.f));
	HeartColors.Add(FLinearColor(1.f, 1.f, 0.f, 1.f));
}

void AHealthPickUp::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	IPickup* Interface = Cast<IPickup>(OtherActor);
	if (Interface)
	{
		switch (HeartType)
		{
		case EHeartType::EHT_AddHealth:
			Interface->AddHealth(this);
			break;
		case EHeartType::EHT_SetHealth:
			Interface->SetHealth(this);
			break;
		case EHeartType::EHT_SetMaxHealth:
			Interface->SetMaxHealth(this);
			break;
		case EHeartType::EHT_AddBothHealth:
			Interface->AddBothHealth(this);
			break;
		default:
			break;
		}
		SpawnPickUpSystem();
		SpawnPickUpSound();
		Destroy();
	}
}

void AHealthPickUp::BeginPlay()
{
	Super::BeginPlay();
	TEnumAsByte<EHeartType> Type(HeartType);
	ChangeColorEffect(HeartColors[Type]);
}

void AHealthPickUp::ChangeColorEffect(FLinearColor Color)
{
	if (ItemEffect)
	{
		ItemEffect->SetVariableLinearColor(FName("Color01"), Color);
	}
}
