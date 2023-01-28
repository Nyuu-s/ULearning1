// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Characters/CharacterTypes.h"
#include "Enemy.generated.h"


class UHealthBarComponent;
class UPawnSensingComponent;
class AAIController;
class AWeapon;
class ASoul;

UCLASS()
class PROJECT935_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()
public:
	AEnemy();

	/* <AActor> */
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void  Destroyed() override;
	/* </AActor> */

	/* <IHitInterface */
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;
	/* </IHitInterface */

protected:
	/* <AActor> */
	virtual void BeginPlay() override;
	/* </AActor> */

	/* <ABaseCharacter> */
	virtual void Die_Implementation() override;
	void SpawnSoul();
	virtual void HandleDamge(float DamageAmount) override;
	virtual void Attack() override;
	virtual bool CanAttack() override;
	virtual void AttackEnd() override;
	/* </ABaseCharacter> */

	UPROPERTY(BlueprintReadOnly)
	EEnemyState EnemyState = EEnemyState::EES_Patrolling;



private:

	/* AI BEHAVIOUR */
	
	void InitializeEnemy();
	void CheckPatrolTarget();
	void CheckCombatTarget();
	void PatrolTimerFinished();
	void HideHealthBar();
	void ShowHealthBar();
	void LoseInterest();
	void StartPatrolling();
	void ChaseTarget();
	bool IsOutsideCombatRadius();
	bool IsOutsideAttackRadius();
	bool IsInsideAttackRadius();
	bool IsAttacking();
	bool IsChasing();
	bool IsDead();
	bool isEngaged();
	void ClearPatrolTimer();
	void StartAttackTimer();
	void ClearAttackTimer();
	bool InTargetRange(AActor* Target, double Radius);
	void MoveToTarget(AActor* Target);
	AActor* ChosePatrolTarget();
	void SpawnDefaultWeapon();

	UFUNCTION()
	void PawnSeen(APawn* SeenPawn); // Callback for OnPawnSeen in UPawnSensingComponent

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPawnSensingComponent> SensingComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UHealthBarComponent> HealthBarWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeapon> WeaponClass;

	UPROPERTY()
	TObjectPtr<AAIController> EnemyAIController;


	UPROPERTY(EditAnywhere, Category = "Combat")
	double CombatRadius = 500.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	double AttackRadius = 150.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	double AcceptanceRadius = 100.f;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	double PatrolRadius = 200.f;

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	TObjectPtr<AActor> PatrolTarget;

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	TArray<AActor*> PatrolTargets;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float PatrolWaitTimeMin = 5.f;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float PatrolWaitTimeMax = 10.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float PatrollingSpeed = 125.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackMin = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackMax = 1.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float ChasingSpeed = 500.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float DeathLifeSpan = 8.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<ASoul> SoulClass;


	FTimerHandle PatrolTimer;
	FTimerHandle AttackTimer;

};

