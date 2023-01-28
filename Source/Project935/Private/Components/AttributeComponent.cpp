// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AttributeComponent.h"


UAttributeComponent::UAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;


}

void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

		
}

void UAttributeComponent::RecieveDamage(float Damage)
{
	Health = FMath::Clamp(Health - Damage,0.f, MaxHealth);
}

void UAttributeComponent::UseStamina(float StaminaAmount)
{
	Stamina = FMath::Clamp(Stamina - StaminaAmount, 0.f, MaxStamina);

}

float UAttributeComponent::GetHealthPercent()
{
	return Health / MaxHealth;
}

float UAttributeComponent::GetStaminaPercent()
{
	return Stamina / MaxStamina;
}

bool UAttributeComponent::IsAlive()
{
	return Health > 0.f;
}

void UAttributeComponent::AddSouls(int32 SoulsAmount)
{
	Soul += SoulsAmount;
}

void UAttributeComponent::AddGold(int32 GoldAmount)
{
	Gold += GoldAmount;
}

void UAttributeComponent::AddHealth(float Amount)
{
	Health = FMath::Clamp(Health + Amount, 1, MaxHealth);
}

void UAttributeComponent::AddMaxHealth(float Amount)
{
	MaxHealth += Amount;
}



void UAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UAttributeComponent::RegenStamina(float DeltaTime)
{
	Stamina = FMath::Clamp(Stamina + StaminaRegenRate * DeltaTime, 0.f, MaxStamina);
}

