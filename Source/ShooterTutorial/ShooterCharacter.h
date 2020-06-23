// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;

UCLASS()
class SHOOTERTUTORIAL_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintPure)
	bool IsDead() const;
	
	UFUNCTION(BlueprintPure)
	int GetHealth() const;

	UFUNCTION(BlueprintPure)
	float GetHealthAsPecentage() const;

	UFUNCTION(BlueprintPure)
	float GetWeaponSpreadMinimum() const;

	UFUNCTION(BlueprintPure)
	float GetWeaponSpreadMaximum() const;

	UFUNCTION(BlueprintPure)
	int GetClip() const;

	UFUNCTION(BlueprintPure)
	int GetRemainingAmmo() const;

	UFUNCTION(BlueprintPure)
	float GetClipAsPrecentage() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	void Shoot();

	void Reload();

private:

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);
	// void LookUp(float AxisValue);

	UPROPERTY(EditAnywhere)
	float RotationRate = 700;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth;

	UPROPERTY(VisibleAnywhere)
	float Health;

	UPROPERTY(VisibleAnywhere)
	AGun* Gun;
};