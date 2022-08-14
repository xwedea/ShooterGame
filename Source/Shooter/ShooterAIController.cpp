// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"


void AShooterAIController::BeginPlay() {
	Super::BeginPlay();

	MainPlayer = Cast<AShooterCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (AIBehavior) {
		RunBehaviorTree(AIBehavior);
		BBComponent = GetBlackboardComponent();
		BBComponent->SetValueAsVector("StartLocation", GetPawn()->GetActorLocation());
	}

}

void AShooterAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	// if (LineOfSightTo(MainPlayer)) {
	// 	BBComponent->SetValueAsVector("PlayerLocation", MainPlayer->GetActorLocation());
	// 	BBComponent->SetValueAsVector("LastKnownPlayerLocation", MainPlayer->GetActorLocation());
	// }
	// else {
	// 	BBComponent->ClearValue("PlayerLocation");
		
	// }

}


