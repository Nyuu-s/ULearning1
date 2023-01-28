// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Project935AnimInstance.h"
#include "Characters/Project935Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UProject935AnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	MainCharacter = Cast<AProject935Character>(TryGetPawnOwner());
	if (MainCharacter) 
	{
		MainCharMovementComponent = MainCharacter->GetCharacterMovement();
	}
}

void UProject935AnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	if (MainCharMovementComponent)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(MainCharMovementComponent->Velocity);
		IsFalling = MainCharMovementComponent->IsFalling();
		CharacterState = MainCharacter->GetCharacterState();
		ActionState = MainCharacter->GetActionState();
		DeathPose = MainCharacter->GetDeathPose();
	}
}
