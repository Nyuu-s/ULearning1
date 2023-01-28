// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MainOverlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UMainOverlay::SetHealthBarPercent(float percent)
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetPercent(percent);
	}
}

void UMainOverlay::SetStaminaBarPercent(float percent)
{
	if (StaminaProgressBar)
	{
		StaminaProgressBar->SetPercent(percent);
	}
}

void UMainOverlay::SetHealthText(float Health, float MaxHealth)
{
	if (HealthText)
	{
		
		HealthText->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), FMath::CeilToInt(Health), FMath::CeilToInt(MaxHealth) )));
	}
}

void UMainOverlay::SetCoin(int32 CoinAmount)
{
	if (CoinCount)
	{
		CoinCount->SetText(FText::FromString(FString::Printf(TEXT("%d"), CoinAmount)));
	}
}

void UMainOverlay::SetSouls(int32 SoulAmount)
{
	if (SoulsCount)
	{
		SoulsCount->SetText(FText::FromString(FString::Printf(TEXT("%d"), SoulAmount)));
	}
}
