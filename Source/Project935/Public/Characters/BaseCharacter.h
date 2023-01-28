// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/HitInterface.h"
#include "Characters/CharacterTypes.h"

#include "BaseCharacter.generated.h"

class AWeapon;
class UAttributeComponent;
class UAnimMontage;

UCLASS()
class PROJECT935_API ABaseCharacter : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:

	ABaseCharacter();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter);
	virtual void Attack();
	void DirectionalHitReact(const FVector& ImpactPoint);
	virtual void HandleDamge(float DamageAmount);
	void PlayHitSound(const FVector& ImpactPoint);
	void SpawnHitParticles(const FVector& ImpactPoint);
	void DisableCapsule();
	void DisableMeshCollision();
	virtual bool CanAttack();
	bool IsAlive();

	void PlayHitReactMontage(const FName& SectionName);
	void StopAttackMontage();
	virtual int32 PlayAttackMontage();
	virtual int32 PlayDodgeMontage();
	virtual int32 PlayDeathMontage();

	UFUNCTION(BlueprintNativeEvent)
	void Die();

	UFUNCTION(BLueprintCallable)
		FVector GetTranslationWarpTarger();

	UFUNCTION(BLueprintCallable)
		FVector GetRotationWarpTarger();

	UFUNCTION(BLueprintCallable)
	void SetWeaponCollisonEnable(ECollisionEnabled::Type CollisionEnabled);

	UFUNCTION(BlueprintCallable)
	virtual void AttackEnd();

	UFUNCTION(BlueprintCallable)
	virtual void DodgeEnd();

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	TObjectPtr<AWeapon> EquippedWeapon;

	UPROPERTY(VisibleAnywhere, Category = Attributes)
	TObjectPtr<UAttributeComponent> Attributes;

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
		TObjectPtr<AActor> CombatTarget;

	UPROPERTY(BlueprintReadOnly)
		TEnumAsByte<EDeathPose> DeathPose;

	UPROPERTY(EditAnywhere, Category = "Combat")
	double WarpTargetDistance = 75.f;

private:
	void PlayMontageSection(UAnimMontage* Montage, const FName& SectionName);
	int32 PlayRandomMontageSection(UAnimMontage* Montage, const TArray<FName>& SectionNames);

	UPROPERTY(EditDefaultsOnly, Category = "Montages | Attack")
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages | Attack")
	TArray<FName> AttackMontageSections;

	UPROPERTY(EditDefaultsOnly, Category = "Montages | Hits")
	TObjectPtr<UAnimMontage> HitReactMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages | Death")
	TObjectPtr<UAnimMontage> DeathMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages | Death")
	TArray<FName> DeathMontageSections;

	UPROPERTY(EditDefaultsOnly, Category = "Montages | Dodge")
	TObjectPtr<UAnimMontage> DodgeMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages | Dodge")
	TArray<FName> DodgeMontageSections;


	UPROPERTY(EditAnywhere, Category = Sounds)
	TObjectPtr<USoundBase> HitSound;

	UPROPERTY(EditAnywhere, Category = VisualEffects)
	TObjectPtr<UParticleSystem> HitParticles;

public:
	FORCEINLINE TEnumAsByte<EDeathPose> GetDeathPose() const { return DeathPose; }
};
