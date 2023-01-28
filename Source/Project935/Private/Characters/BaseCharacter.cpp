



#include "Characters/BaseCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/AttributeComponent.h"
#include "Items/Weapons/Weapon.h"
#include "Kismet/GameplayStatics.h"


ABaseCharacter::ABaseCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	Attributes = CreateDefaultSubobject<UAttributeComponent>(TEXT("Attributes"));
}


bool ABaseCharacter::CanAttack()
{
	return false;
}

void ABaseCharacter::AttackEnd()
{
}

void ABaseCharacter::DodgeEnd()
{
}

void ABaseCharacter::GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter)
{
	if (IsAlive() && Hitter)
	{
		DirectionalHitReact(Hitter->GetActorLocation());
	}
	else Die();

	PlayHitSound(ImpactPoint);
	SpawnHitParticles(ImpactPoint);
}

void ABaseCharacter::Attack()
{
	if(CombatTarget && CombatTarget->ActorHasTag(FName("Dead"))) 
		CombatTarget = nullptr;

}

bool ABaseCharacter::IsAlive()
{
	return Attributes && Attributes->IsAlive();
}

void ABaseCharacter::DisableCapsule()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABaseCharacter::DisableMeshCollision()
{
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABaseCharacter::PlayHitSound(const FVector& ImpactPoint)
{
	if (HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, ImpactPoint);
	}
}

void ABaseCharacter::SpawnHitParticles(const FVector& ImpactPoint)
{
	if (HitParticles && GetWorld())
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, ImpactPoint);
	}
}

void ABaseCharacter::HandleDamge(float DamageAmount)
{
	if (Attributes)
	{
		Attributes->RecieveDamage(DamageAmount);
	}
}

int32 ABaseCharacter::PlayAttackMontage() 
{
	return PlayRandomMontageSection(AttackMontage, AttackMontageSections);
}

int32 ABaseCharacter::PlayDodgeMontage()
{
	return PlayRandomMontageSection(DodgeMontage, DodgeMontageSections);
}

int32 ABaseCharacter::PlayDeathMontage()
{
	const int32 Selection = PlayRandomMontageSection(DeathMontage, DeathMontageSections);
	TEnumAsByte<EDeathPose> Pose(Selection);
	if (Pose < EDeathPose::EDP_MAX)
	{
		DeathPose = Pose;
	}
	return Selection;
}

FVector ABaseCharacter::GetTranslationWarpTarger()
{
	if(CombatTarget == nullptr) return FVector();

	const FVector CombatTargetLocation = CombatTarget->GetActorLocation();
	const FVector Location = GetActorLocation();

	const FVector TargetToMe = (Location - CombatTargetLocation).GetSafeNormal() * WarpTargetDistance;
	return CombatTargetLocation + TargetToMe;
	
}

FVector ABaseCharacter::GetRotationWarpTarger()
{
	if (CombatTarget)
	{
		return CombatTarget->GetActorLocation();
	}
	return FVector();
}

void ABaseCharacter::PlayMontageSection(UAnimMontage* Montage, const FName& SectionName)
{
	UAnimInstance* Instance = GetMesh()->GetAnimInstance();
	if (Instance && Montage)
	{
		Instance->Montage_Play(Montage);
		Instance->Montage_JumpToSection(SectionName, Montage);

	}
}

int32 ABaseCharacter::PlayRandomMontageSection(UAnimMontage* Montage, const TArray<FName>& SectionNames)
{
	if (SectionNames.Num() <= 0) return -1;
	const int32 MaxSectionIndex = SectionNames.Num() - 1;
	const int32 Selection = FMath::RandRange(0, MaxSectionIndex);
	PlayMontageSection(Montage, SectionNames[Selection]);
	return Selection;
}

void ABaseCharacter::PlayHitReactMontage(const FName& SectionName)
{
	UAnimInstance* Instance = GetMesh()->GetAnimInstance();
	if (Instance && HitReactMontage)
	{
		Instance->Montage_Play(HitReactMontage);
		Instance->Montage_JumpToSection(SectionName, HitReactMontage);
	}
}

void ABaseCharacter::StopAttackMontage()
{
	UAnimInstance* Instance = GetMesh()->GetAnimInstance();
	if (Instance)
	{
		Instance->Montage_Stop(0.25f,AttackMontage);
	}
}

void ABaseCharacter::DirectionalHitReact(const FVector& ImpactPoint)
{
	const FVector Forward = GetActorForwardVector();
	const FVector ImpactPointLowered = FVector(ImpactPoint.X, ImpactPoint.Y, GetActorLocation().Z);
	const FVector ToHit = (ImpactPointLowered - GetActorLocation()).GetSafeNormal();

	//Forward . ToHit = |Forward| * |ToHit| * cos(theta)
	//					    =1		 =1
	//Forward . ToHit = cos(theta)
	const double costheta = FVector::DotProduct(Forward, ToHit);
	double theta = FMath::Acos(costheta);
	//convert from radians to degrees
	theta = FMath::RadiansToDegrees(theta);

	//if cp points down theta is negative 
	const FVector crossProduct = FVector::CrossProduct(Forward, ToHit);
	if (crossProduct.Z < 0) {
		theta *= -1.f;
	}


	FName Section("FromBack");
	if (theta >= -45.f && theta < 45.f)
	{
		Section = FName("FromFront");
	}
	else if (theta >= -135.f && theta < -45.f)
	{
		Section = FName("FromLeft");
	}
	else if (theta >= 45.f && theta < 135.f)
	{
		Section = FName("FromRight");
	}


	PlayHitReactMontage(Section);
}

void ABaseCharacter::Die_Implementation()
{
	Tags.Add(FName("Dead"));
	PlayDeathMontage();
}


void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseCharacter::SetWeaponCollisonEnable(ECollisionEnabled::Type CollisionEnabled)
{
	if (EquippedWeapon && EquippedWeapon->GetWeaponBox())
	{
		EquippedWeapon->GetWeaponBox()->SetCollisionEnabled(CollisionEnabled);
		EquippedWeapon->IgnoreActors.Empty();
	}
}


