// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"


void AShooterController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner) 
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    if(HudScreen != nullptr)
    {
        HudScreen->RemoveFromViewport();
    }

    if(bIsWinner)
    {
        UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
        if(WinScreen != nullptr)
        {
            WinScreen->AddToViewport();
        }
        GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
    }
    else
    {
        UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
        if(LoseScreen != nullptr)
        {
            LoseScreen->AddToViewport();
        }
        GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
    }
}

void AShooterController::BeginPlay() 
{
    Super::BeginPlay();

    HudScreen = CreateWidget(this, HudScreenClass);
    if(HudScreen != nullptr)
    {
        HudScreen->AddToViewport();
    }
}
