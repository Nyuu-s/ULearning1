// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT935_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UAttributeComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void RegenStamina(float DeltaTime);
protected:

	virtual void BeginPlay() override;

private:
	//Current health value
	UPROPERTY(EditAnywhere, Category = "Actor Attributes");
	float Health;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes");
	float MaxHealth;	
	
	//Current health value
	UPROPERTY(EditAnywhere, Category = "Actor Attributes");
	float Stamina;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes");
	float MaxStamina;

	UPROPERTY(EditAnywhere , Category = "Actor Attributes")
	int32 Gold;

	UPROPERTY(EditAnywhere , Category = "Actor Attributes")
	int32 Soul;	
	
	UPROPERTY(EditAnywhere , Category = "Actor Attributes")
	float DodgeCost = 14.f;	
	
	UPROPERTY(EditAnywhere , Category = "Actor Attributes")
	float StaminaRegenRate = 8.f;

public:
	void RecieveDamage(float Damage);
	void UseStamina(float StaminaAmount);
	float GetHealthPercent();
	float GetStaminaPercent();
	bool IsAlive();
	void AddSouls(int32 SoulsAmount);
	void AddGold(int32 GoldAmount);
	void AddHealth(float Amount);
	void AddMaxHealth(float Amount);
	FORCEINLINE int32 GetGold() const { return Gold; }
	FORCEINLINE int32 GetSouls() const { return Soul; }
	FORCEINLINE float GetDodgeCost() const { return DodgeCost; }
	FORCEINLINE float GetCurrentStamina() const { return Stamina; }
	FORCEINLINE float GetHealth() const { return Health; }
	FORCEINLINE float GetHealthMax() const { return MaxHealth; }
	FORCEINLINE void SetHealth(float Amount) { Health = Amount; }
	FORCEINLINE void SetMaxHealth(float Amount) { MaxHealth = Amount; }

		
};
