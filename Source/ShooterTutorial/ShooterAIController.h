// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERTUTORIAL_API AShooterAIController : public AAIController
{
	GENERATED_BODY()
public:
	AShooterAIController();
	
	bool IsDead() const;

	bool CanSeePlayer() const;
	
//AI Configs
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	class UAISenseConfig_Sight* SightConfig;	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	class UAISenseConfig_Hearing* HearingConfig;

	UFUNCTION()
	void OnPawnDetected(const TArray<AActor*> &DetectedPawns);

	virtual void Tick(float DeltaTime) override;

	virtual FGenericTeamId GetGenericTeamId() const; 
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(VisibleAnywhere)
	APawn* PlayerPawn;

	UPROPERTY(EditAnywhere)
	float AcceptanceRadius = 200;

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior;

//AI Sight Setting

	UPROPERTY(EditDefaultsOnly, Category = "AI Sight")
	float AISightRadius = 500;

	UPROPERTY(EditDefaultsOnly, Category = "AI Sight")
	float AISightAge = 5;

	UPROPERTY(EditDefaultsOnly, Category = "AI Sight")
	float AILoseSightRadius = AISightRadius + 50;

	UPROPERTY(EditDefaultsOnly, Category = "AI Sight")
	float AIFieldofView = 90;
	
	UPROPERTY(EditDefaultsOnly, Category = "AI Sight")
	float AutoSuccessRangeFromLastSeenLocation = 200;

//AI Hearing Settings

	UPROPERTY(EditDefaultsOnly, Category = "AI Hearing")
	float AIHearingRange = 200;
	UPROPERTY(EditDefaultsOnly, Category = "AI Hearing")
	float AILossHearingRange = AIHearingRange + 50;

//AI tasks variables

	UPROPERTY(VisibleAnywhere)
	bool bCanSeePlayer = false;

	UPROPERTY(EditAnywhere)
	FGenericTeamId TeamId = FGenericTeamId(0);

//Manual Override for Sensing Actors
	TArray<AActor*> OutActorList;

};
