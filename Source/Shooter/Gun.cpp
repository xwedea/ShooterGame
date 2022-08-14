// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
	

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger() {
	// UE_LOG(LogTemp, Display, TEXT("Shoot()"))
	APawn * OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) return;
	AController * OwnerController = OwnerPawn->GetController();
	if (!OwnerController) return;

	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, "MuzzleFlashSocket");
	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	
	FVector EndLoc = Location + Rotation.Vector() * MaxRange;
	
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	FHitResult Hit;
	bool bHit = GetWorld()->LineTraceSingleByChannel(
		Hit,
		Location,
		EndLoc,
		ECollisionChannel::ECC_GameTraceChannel1,
		Params
	);	
	// DrawDebugLine(GetWorld(), Location, EndLoc, FColor::Purple, true);

	FVector ShotDirection = Rotation.Vector();
	if (bHit) {
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			ImpactParticle,
			Hit.Location,
			ShotDirection.Rotation(),
			true
		);
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 10, 10, FColor::Red, false, 1.f);
		FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
		AActor * HitActor = Hit.GetActor();
		if (HitActor) {
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}

	UE_LOG(LogTemp, Display, TEXT("PullTrigger(), bHit=%d"), bHit);


}