// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Soul.h"
#include "Interfaces/Pickup.h"
#include "Kismet/KismetSystemLibrary.h"

void ASoul::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (DesiredZ > GetActorLocation().Z) return;
	AddActorWorldOffset(FVector(0.f, 0.f, DeltaTime * -DriftRate));
}

void ASoul::BeginPlay()
{
	Super::BeginPlay();
	FVector Start = GetActorLocation();
	FVector EndTrace = Start - FVector(0.f, 0.f, 3000.f);
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());
	ObjectTypesArray.Add(EObjectTypeQuery::ObjectTypeQuery1);
	FHitResult HitTrace;

	UKismetSystemLibrary::LineTraceSingleForObjects(
		this,
		Start,
		EndTrace,
		ObjectTypesArray,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		HitTrace,
		true
	);
	DesiredZ = HitTrace.ImpactPoint.Z + DesiredHeight;
	

}

void ASoul::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IPickup* PickupInterface = Cast<IPickup>(OtherActor);
	if (PickupInterface)
	{
		PickupInterface->AddSouls(this);
		SpawnPickUpSystem();
		SpawnPickUpSound();
		Destroy();
	}
}
