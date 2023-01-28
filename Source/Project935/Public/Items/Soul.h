// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Soul.generated.h"



/**
 * 
 */
UCLASS()
class PROJECT935_API ASoul : public AItem
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:
	UPROPERTY(EditAnywhere, Category = "Soul Properties")
	int32 SoulValue = 10;

	UPROPERTY(EditAnywhere, Category = "Soul Properties")
	float DesiredHeight = 50.f;

	UPROPERTY(EditAnywhere, Category = "Soul Properties")
		float DriftRate = 15.f;

	float DesiredZ;

public:
	FORCEINLINE int32 GetSoulValue() const { return SoulValue; }
	FORCEINLINE void SetSoulValue(int32 SoulNumber) { SoulValue = SoulNumber; }


};
