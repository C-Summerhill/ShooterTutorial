// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SHOOTERTUTORIAL_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	void PullTrigger();

	void Reload();

	float GetWeaponSpreadMinimum() const;

	float GetWeaponSpreadMaximum() const;

	int GetClip() const;

	int GetRemainingAmmo() const;

	float GetClipAsPrecentage() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
	UParticleSystem* HitWall;

	UPROPERTY(EditAnywhere)
	float MaxRange = 1000;

	UPROPERTY(EditAnywhere)
	float Damage = 10;

	UPROPERTY(EditDefaultsOnly)
	float WeaponSpreadMinimum = 1;

	UPROPERTY(EditDefaultsOnly)
	float WeaponSpreadMaximum = 3;

// Ammo Code

	UPROPERTY(EditAnywhere)
	int MaxClip = 20;

	UPROPERTY(EditAnywhere)
	int Clip;

	UPROPERTY(EditAnywhere)
	int MaxRemainingAmmo = 80;

	UPROPERTY(EditAnywhere)
	int RemainingAmmo;

	//How long it takes to reload
	UPROPERTY(EditAnywhere)
	float ReloadDelay = 1;

	//Leave at 0 to set to max ammo
	UPROPERTY(EditDefaultsOnly)
	int StartingRemainingAmmo = 0;

	//Leave at 0 to set to max ammo
	UPROPERTY(EditDefaultsOnly)
	int StartingClipAmmo = 0;

	UPROPERTY(EditAnywhere)
	USoundBase* ReloadSound;

//~ Ammo Code

	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);

	AController* GetOwnerController() const;

	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere)
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere)
	USoundBase* DryFire;
};
