// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Project935Character.h"
#include "EnhancedInputSubsystems.h"

#include "Components/InputComponent.h"
#include "Components/AttributeComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "GroomComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Items/Item.h"
#include "Items/Weapons/Weapon.h"
#include "Animation/AnimMontage.h"
#include "HUD/MainHUD.h"
#include "HUD/MainOverlay.h"
#include "Items/Soul.h"
#include "Items/Treasure.h"
#include "Items/HealthPickUp.h"


AProject935Character::AProject935Character()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);

	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->TargetArmLength = 300.f;
	CameraBoom->SetupAttachment(GetRootComponent());
	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(CameraBoom);

	Hair = CreateDefaultSubobject<UGroomComponent>(TEXT("Hair"));
	Hair->SetupAttachment(GetMesh());
	Hair->AttachmentName = FString("headSocket");

	Eyebrows = CreateDefaultSubobject<UGroomComponent>(TEXT("Eyebrows"));
	Eyebrows->SetupAttachment(GetMesh());
	Eyebrows->AttachmentName = FString("headSocket");
}

void AProject935Character::Tick(float DeltaTime)
{
	if (Attributes && MainOverlay)
	{
		Attributes->RegenStamina(DeltaTime);
		MainOverlay->SetStaminaBarPercent(Attributes->GetStaminaPercent());
	}
}

void AProject935Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhanceInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhanceInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AProject935Character::Move);
		EnhanceInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AProject935Character::Look);
		EnhanceInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AProject935Character::Jump);
		EnhanceInputComponent->BindAction(EquipAction, ETriggerEvent::Triggered, this, &AProject935Character::EKeyPressed);
		EnhanceInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AProject935Character::Attack);
		EnhanceInputComponent->BindAction(DodgeAction, ETriggerEvent::Triggered, this, &AProject935Character::Dodge);
		
	}

}

void AProject935Character::SetOverlappingItem(AItem* Item)
{
	OverlappingItem = Item;
}

void AProject935Character::AddSouls(ASoul* Soul)
{
	
	if (Attributes && MainOverlay) 
	{
		Attributes->AddSouls(Soul->GetSoulValue());
		MainOverlay->SetSouls(Attributes->GetSouls());
	}
}

void AProject935Character::AddGold(ATreasure* Gold)
{
	if (Attributes && MainOverlay)
	{
		Attributes->AddGold(Gold->GetGoldValue());
		MainOverlay->SetCoin(Attributes->GetGold());
	}
}

void AProject935Character::AddHealth(AHealthPickUp* Heart)
{
	if (Heart == nullptr) return;
	if (Attributes && MainOverlay)
	{
		Attributes->AddHealth(Heart->HealValue);
		UpdateHUDHealth();
	}
}

void AProject935Character::SetHealth(AHealthPickUp* Heart)
{
	if (Heart == nullptr) return;
	if (Attributes && MainOverlay)
	{
		Attributes->SetHealth(Heart->HealValue);
		UpdateHUDHealth();
	}
}

void AProject935Character::SetMaxHealth(AHealthPickUp* Heart)
{
	if (Heart == nullptr) return;
	if (Attributes && MainOverlay)
	{
		Attributes->AddMaxHealth(Heart->HealthMaxValue);
		UpdateHUDHealth();
	}
}

void AProject935Character::AddBothHealth(AHealthPickUp* Heart)
{
	if (Heart == nullptr) return;
	if (Attributes && MainOverlay)
	{
		Attributes->AddMaxHealth(Heart->HealthMaxValue);
		Attributes->AddHealth(Heart->HealValue);
		UpdateHUDHealth();
	}
}



void AProject935Character::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(FName("Player"));

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if(UEnhancedInputLocalPlayerSubsystem* SubSysteme = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			SubSysteme->AddMappingContext(MainCharContext, 0);
		}
		
		InitializeMainOverlay(PlayerController);


	}

	

}



void AProject935Character::GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter)
{
	Super::GetHit_Implementation(ImpactPoint, Hitter);
	SetWeaponCollisonEnable(ECollisionEnabled::NoCollision);
	if (Attributes && Attributes->GetHealthPercent() > 0.f)
	{
		ActionState = EActionState::ECS_HitReaction;
	}
}

void AProject935Character::Move(const FInputActionValue& Value)
{
	if (ActionState != EActionState::EAS_Unoccupied) return; 
	const FVector2D MovementVector = Value.Get<FVector2D>();
	
	const FRotator ControllerRotation = GetControlRotation();
	const FRotator YawRotation(0.f, ControllerRotation.Yaw,0.f);
	AddMovementInput(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X), MovementVector.Y);
	AddMovementInput(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y), MovementVector.X);

	
}

void AProject935Character::Look(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(LookVector.Y);
}

void AProject935Character::Dodge()
{
	if (!isOccupied() || !HasEnoughStamina()) return;
	PlayDodgeMontage();
	ActionState = EActionState::EAS_Dodge;
	if (Attributes && MainOverlay)
	{
		Attributes->UseStamina(Attributes->GetDodgeCost());
		MainOverlay->SetStaminaBarPercent(Attributes->GetStaminaPercent());
	}
}



void AProject935Character::EKeyPressed()
{
	AWeapon* OverlappingWeapon = Cast<AWeapon>(OverlappingItem);
	if (OverlappingWeapon)
	{
		if (EquippedWeapon)
		{
			EquippedWeapon->Destroy();
		}
		EquipWeapon(OverlappingWeapon);
	}
	else
	{
		if (CanDisarm())
		{
			Disarm();
			
		}
		else if (CanArm())
		{
			Arm();
		}
	}
}

void AProject935Character::Jump()
{
	if (IsUnoccupied()) return;
	Super::Jump();
}


void AProject935Character::PlayEquipMontage(const FName& SectionName)
{
	UAnimInstance* Instance = GetMesh()->GetAnimInstance();
	if (Instance && EquipMontage)
	{
		Instance->Montage_Play(EquipMontage);
		Instance->Montage_JumpToSection(SectionName, EquipMontage);
	}
}

bool AProject935Character::CanDisarm()
{
	return ActionState == EActionState::EAS_Unoccupied
		&& CharacterState != ECharacterState::ECS_Unequipped;
}

bool AProject935Character::CanArm()
{
	return ActionState == EActionState::EAS_Unoccupied
		&& CharacterState == ECharacterState::ECS_Unequipped
		&& EquippedWeapon;

}

void AProject935Character::Disarm()
{
	PlayEquipMontage(FName("Unequip"));
	CharacterState = ECharacterState::ECS_Unequipped;
	ActionState = EActionState::EAS_EquippingWeapon;
}

void AProject935Character::Arm()
{
	PlayEquipMontage(FName("Equip"));
	CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
	ActionState = EActionState::EAS_EquippingWeapon;
}

void AProject935Character::EquipWeapon(AWeapon* Weapon)
{
	Weapon->Equip(GetMesh(), FName("RightHandSocket"), this, this);
	CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
	OverlappingItem = nullptr;
	EquippedWeapon = Weapon;
}

bool AProject935Character::HasEnoughStamina()
{
	return Attributes && (Attributes->GetCurrentStamina() - Attributes->GetDodgeCost()) >= 0.f;
}

bool AProject935Character::isOccupied()
{
	return ActionState == EActionState::EAS_Unoccupied;
}

void AProject935Character::Attack()
{
	Super::Attack();
	if (CanAttack())
	{
		PlayAttackMontage();
		ActionState = EActionState::EAS_Attacking;
		
	}
}

bool AProject935Character::CanAttack()
{
	return (ActionState == EActionState::EAS_Unoccupied) && (CharacterState != ECharacterState::ECS_Unequipped);
}

void AProject935Character::AttackEnd()
{
	ActionState = EActionState::EAS_Unoccupied;
}

void AProject935Character::DodgeEnd()
{
	Super::DodgeEnd();
	ActionState = EActionState::EAS_Unoccupied;
}

float AProject935Character::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	HandleDamge(DamageAmount);
	UpdateHUDHealth();
	return DamageAmount;
}

void AProject935Character::Die_Implementation()
{
	Super::Die_Implementation();

	ActionState = EActionState::EAS_Dead;
	DisableMeshCollision();
}



void AProject935Character::AttackWeaponToBack()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->AttachMeshToSocket(GetMesh(), FName("SpineSocket"));
	}
}

void AProject935Character::AttachWeaponToHand()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->AttachMeshToSocket(GetMesh(), FName("RightHandSocket"));
	}
}

void AProject935Character::FinishEquipping()
{

	ActionState = EActionState::EAS_Unoccupied;
}

void AProject935Character::HitReactEnd()
{
	ActionState = EActionState::EAS_Unoccupied;
}

bool AProject935Character::IsUnoccupied()
{
	return ActionState != EActionState::EAS_Unoccupied;
}

void AProject935Character::UpdateHUDHealth()
{
	if (MainOverlay && Attributes)
	{
		
		MainOverlay->SetHealthBarPercent(Attributes->GetHealthPercent());
		MainOverlay->SetHealthText(Attributes->GetHealth(), Attributes->GetHealthMax());
	}
}

void AProject935Character::InitializeMainOverlay(APlayerController* PlayerController)
{
	if (AMainHUD* HUD = Cast<AMainHUD>(PlayerController->GetHUD()))
	{
		MainOverlay = HUD->GetMainOverlay();
		if (MainOverlay && Attributes)
		{
			MainOverlay->SetHealthBarPercent(Attributes->GetHealthPercent());
			MainOverlay->SetStaminaBarPercent(1.f);
			MainOverlay->SetCoin(0);
			MainOverlay->SetSouls(0);
			MainOverlay->SetHealthText(Attributes->GetHealth(),Attributes->GetHealthMax());
		}
		
	}
}











