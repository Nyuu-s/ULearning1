// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/HitInterface.h"
#include "BreakableActor.generated.h"

class UGeometryCollectionComponent;
class UCapsuleComponent;


UCLASS()
class PROJECT935_API ABreakableActor : public AActor, public IHitInterface
{
	GENERATED_BODY()
	
public:	

	ABreakableActor();
	virtual void Tick(float DeltaTime) override;
	virtual void GetHit_Implementation(const FVector& ImpactPoint , AActor* Hitter) override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCapsuleComponent> Capsule;

	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UGeometryCollectionComponent> GeometryCollection;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class AItem>> TreasureClasses;

	bool bBroken = false;


};
