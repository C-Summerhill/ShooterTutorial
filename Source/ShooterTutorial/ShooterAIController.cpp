// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"


void AShooterAIController::BeginPlay() 
{
    Super::BeginPlay();

    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if(AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior);
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
    }
}

bool AShooterAIController::IsDead() const
{
    AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());
    if(ControlledCharacter != nullptr)
    {
        return ControlledCharacter->IsDead();
    }

    return true;
}

bool AShooterAIController::CanSeePlayer() const
{
    return bCanSeePlayer;
}


void AShooterAIController::OnPawnDetected(const TArray<AActor*> &DetectedPawns) 
{   
    for(int i = 0; i < DetectedPawns.Num();i++)
    {
        //UE_LOG(LogTemp, Warning, TEXT("Detected: " + DetectedPawns[i]));

        if (DetectedPawns[i] == PlayerPawn)
        {
            UE_LOG(LogTemp, Warning, TEXT("Player Detected"));
            bCanSeePlayer = true;
            return;
        }        
        
        UE_LOG(LogTemp, Warning, TEXT("Not Player"));
        bCanSeePlayer = false;
    }
}

void AShooterAIController::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);

    GetPerceptionComponent()->GetCurrentlyPerceivedActors(NULL, OutActorList);
    UE_LOG(LogTemp, Warning, TEXT("OutActorList Number: %f"), OutActorList.Num());
    if(OutActorList.Num() < 1)
    {
        bCanSeePlayer = false;
    }
    
}

FGenericTeamId AShooterAIController::GetGenericTeamId() const
{
    return TeamId;
}

AShooterAIController::AShooterAIController() 
{
    PrimaryActorTick.bCanEverTick = true;

    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
    HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));
    SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

    //Sight

    SightConfig->SightRadius = AISightRadius;
    SightConfig->LoseSightRadius = AILoseSightRadius;
    SightConfig->PeripheralVisionAngleDegrees = AIFieldofView;
    SightConfig->SetMaxAge(AISightAge);
    SightConfig->AutoSuccessRangeFromLastSeenLocation = AutoSuccessRangeFromLastSeenLocation;

    SightConfig->DetectionByAffiliation.bDetectEnemies = true;
    SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
    SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

    //Hearing

    HearingConfig->HearingRange = AIHearingRange;
    HearingConfig->LoSHearingRange = AILossHearingRange;

    GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
    
    //This doesn't trigger should their be no more pawns in view, attempting manual override
    //GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AShooterAIController::OnPawnDetected);
    
    GetPerceptionComponent()->ConfigureSense(*SightConfig);
    GetPerceptionComponent()->ConfigureSense(*HearingConfig);

}