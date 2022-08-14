// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "ShooterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot() {
	NodeName = "Shoot Baby";
}

EBTNodeResult::Type 
UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);


	if (!OwnerComp.GetAIOwner()) {
		return EBTNodeResult::Failed;
	}
	AShooterCharacter * AIShooter = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (!AIShooter) {
		return EBTNodeResult::Failed;
	}

	AIShooter->Shoot();
	return EBTNodeResult::Succeeded;
}
