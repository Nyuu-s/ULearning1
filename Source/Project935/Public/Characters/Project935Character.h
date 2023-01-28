// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "InputActionValue.h"
#include "CharacterTypes.h"
#include "Interfaces/Pickup.h"
#include "Project935Character.generated.h"


class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UGroomComponent;
class UAnimMontage;
class UMainOverlay;
class AItem;
class ASoul;
class ATreasure;
class AHealthPickUp;




UCLASS()
class PROJECT935_API AProject935Character : public ABaseCharacter, public IPickup
{
	GENERATED_BODY()

public:

	AProject935Character();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void SetOverlappingItem(AItem* Item) override;
	virtual void AddSouls(ASoul* Soul) override;
	virtual void AddGold(ATreasure* Gold) override;
	virtual void AddHealth(AHealthPickUp* Player) override;
	virtual void SetHealth(AHealthPickUp* Heart) override;
	virtual void SetMaxHealth(AHealthPickUp* Heart) override;
	virtual void AddBothHealth(AHealthPickUp* Heart) override;

protected:

	virtual void BeginPlay() override;

	

	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;

	/** Inputs Callbacks */
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Dodge();

	void EKeyPressed();
	virtual void Jump() override;


	/* Combat */
	void PlayEquipMontage(const FName& SectionName) ;
	bool CanDisarm();
	bool CanArm();
	void Disarm();
	void Arm();
	void EquipWeapon(AWeapon* Weapon);
	bool HasEnoughStamina();
	bool isOccupied();
	virtual void Attack() override;
	virtual bool CanAttack() override;
	virtual void AttackEnd() override;
	virtual void DodgeEnd() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Die_Implementation() override;


	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* MainCharContext;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* EquipAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* DodgeAction;

	UFUNCTION(BLueprintCallable)
	void AttackWeaponToBack();

	UFUNCTION(BLueprintCallable)
	void AttachWeaponToHand();

	UFUNCTION(BLueprintCallable)
	void FinishEquipping();

	UFUNCTION(BLueprintCallable)
	void HitReactEnd();
private:

	bool IsUnoccupied();
	void UpdateHUDHealth();
	void InitializeMainOverlay(APlayerController* PlayerController);
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	TObjectPtr<UAnimMontage> EquipMontage;

	/* Character Components */
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;

	UPROPERTY(VisibleAnywhere, Category = Hair)
	UGroomComponent* Hair;

	UPROPERTY(VisibleAnywhere, Category = Hair)
	UGroomComponent* Eyebrows;

	UPROPERTY(VisibleInstanceOnly)
	TObjectPtr<AItem> OverlappingItem;

	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EActionState ActionState = EActionState::EAS_Unoccupied;

	UPROPERTY()
	TObjectPtr<UMainOverlay> MainOverlay;
public:
	

	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
	FORCEINLINE EActionState GetActionState() const { return ActionState; }
};
