// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainOverlay.generated.h"

class UProgressBar;
class UTextBlock;
/**
 * 
 */
UCLASS()

class PROJECT935_API UMainOverlay : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetHealthBarPercent(float percent);
	void SetStaminaBarPercent(float percent);
	void SetHealthText(float Health, float MaxHealth);
	void SetCoin(int32 CoinAmount);
	void SetSouls(int32 SoulAmount);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthProgressBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> StaminaProgressBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CoinCount;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> SoulsCount;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> HealthText;


};
