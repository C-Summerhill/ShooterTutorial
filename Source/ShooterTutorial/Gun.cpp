// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create and set root of object
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

void AGun::PullTrigger() 
{
	if(Clip <= 0)
	{
		UGameplayStatics::SpawnSoundAttached(DryFire, Mesh, TEXT("MuzzleFlashSocket"));
		return;
	}

	Clip--;
	
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));

	FHitResult Hit;
	FVector ShotDirection;
	bool bSuccess = GunTrace(Hit, ShotDirection);
	if(bSuccess)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitWall, Hit.Location, ShotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, Hit.Location);
		AActor* HitActor = Hit.GetActor();
		if(HitActor != nullptr)
		{		
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			AController* OwnerController = GetOwnerController();
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}
}

void AGun::Reload() 
{
	if(RemainingAmmo < 1 || Clip == MaxClip)
		{ return; }
	
	RemainingAmmo += Clip;
	Clip = 0;

	if(RemainingAmmo > MaxClip)
	{
		Clip = MaxClip;
		RemainingAmmo -= MaxClip;
		return;
	}

	Clip = RemainingAmmo;
	RemainingAmmo = 0;
	
}

float AGun::GetWeaponSpreadMinimum() const
{
	return WeaponSpreadMinimum;
}

float AGun::GetWeaponSpreadMaximum() const
{
	return WeaponSpreadMaximum;
}

int AGun::GetClip() const
{
	return Clip;
}

int AGun::GetRemainingAmmo() const
{
	return RemainingAmmo;
}

float AGun::GetClipAsPrecentage() const
{
	return (float) Clip / MaxClip;
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

	//This always start the gun with maximum ammo
	Clip = StartingClipAmmo > 0 ? StartingClipAmmo : MaxClip;
	RemainingAmmo = StartingRemainingAmmo > 0 ? StartingRemainingAmmo : MaxRemainingAmmo;
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection) 
{
	AController* OwnerController = GetOwnerController();
	if(OwnerController==nullptr) 
		return false;

	FVector Location;
	FRotator Rotation;

	OwnerController->GetPlayerViewPoint(Location, Rotation);
	ShotDirection = -Rotation.Vector();

	FVector End = Location + Rotation.Vector() * MaxRange;
	
	//Create a list of targets we can't hit
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(OwnerPawn==nullptr) return nullptr;
	return OwnerPawn->GetController();

}