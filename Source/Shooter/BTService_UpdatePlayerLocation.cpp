// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdatePlayerLocation.h"
#include "GameFramework/Pawn.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_UpdatePlayerLocation::UBTService_UpdatePlayerLocation() {
	NodeName = "Update Player Location";
}

void UBTService_UpdatePlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn * PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!PlayerPawn) return;


	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());

}