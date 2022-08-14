// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "ShooterGameModeBase.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	Gun->SetOwner(this);
	GetMesh()->HideBoneByName("weapon_r", EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "WeaponSocket");

	Health = MaxHealth;

}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookRight", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp_Controller", this, &AShooterCharacter::LookUp_Controller);
	PlayerInputComponent->BindAxis("LookRight_Controller", this, &AShooterCharacter::LookRight_Controller);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AShooterCharacter::Shoot);

}

void AShooterCharacter::Shoot() {
	// UE_LOG(LogTemp, Warning, TEXT("Shoot()"));
	Gun->PullTrigger();
	
}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) {
	float DamageTaken = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	float DamageToApply = FMath::Min(DamageTaken, Health);
	Health -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);

	if (!IsAlive()) {
		AShooterGameModeBase * GameMode = GetWorld()->GetAuthGameMode<AShooterGameModeBase>();
		if (GameMode) {
			GameMode->PawnKilled(this);
		}
 
		// DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	}

	return DamageToApply;
}

bool AShooterCharacter::IsAlive() const {
	return (Health > 0);
}

void AShooterCharacter::LookUp_Controller(float AxisVal) {
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	AddControllerPitchInput(DeltaTime * AxisVal * CameraRotationRate);
}

void AShooterCharacter::LookRight_Controller(float AxisVal) {
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	AddControllerYawInput(DeltaTime * AxisVal * CameraRotationRate);
}

void AShooterCharacter::MoveForward(float AxisVal) {
	AddMovementInput(GetActorForwardVector(), AxisVal);
}

void AShooterCharacter::MoveRight(float AxisVal) {
	AddMovementInput(GetActorRightVector(), AxisVal);
}

