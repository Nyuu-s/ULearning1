// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "HealthPickUp.generated.h"

UENUM()
enum EHeartType 
{
	EHT_AddHealth UMETA(DisplayName = "Increase current health"),
	EHT_SetHealth UMETA(DisplayName = "Change current health"),
	EHT_SetMaxHealth UMETA(DisplayName = "Change Max Health"),
	EHT_AddBothHealth UMETA(DisplayName = "Increase both attributes")
};

/**
 * 
 */
UCLASS()
class PROJECT935_API AHealthPickUp : public AItem
{
	GENERATED_BODY()
public:
	AHealthPickUp();
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	EHeartType GetHeartType() const { return HeartType; }
	UPROPERTY(EditAnywhere)
	float HealValue = 20.f;
	UPROPERTY(EditAnywhere)
	float HealthMaxValue = 0.f;
protected:
	virtual void BeginPlay() override;
private:
	
	void ChangeColorEffect(FLinearColor Color);

	UPROPERTY(EditAnywhere)
	TArray<FLinearColor> HeartColors;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EHeartType> HeartType;

};
