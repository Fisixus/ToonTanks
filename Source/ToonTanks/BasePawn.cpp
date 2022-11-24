// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "Bullet.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = m_CapsuleComp;

	m_BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	m_BaseMesh->SetupAttachment(m_CapsuleComp);

	m_TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	m_TurretMesh->SetupAttachment(m_BaseMesh);

	m_ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	m_ProjectileSpawnPoint->SetupAttachment(m_TurretMesh);
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
}

void ABasePawn::RotateTurret(FVector LookAtTarget, float turnInterpSpeed) const
{
	FVector ToTarget = (LookAtTarget - m_TurretMesh->GetComponentLocation()).GetSafeNormal();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw,0.f);
	m_TurretMesh->SetWorldRotation(FMath::RInterpTo(m_TurretMesh->GetComponentRotation(),
		LookAtRotation,
		UGameplayStatics::GetWorldDeltaSeconds(this),
		turnInterpSpeed));
}

void ABasePawn::Fire(UMaterialInterface* m)
{
	ABullet* bullet = GetWorld()->SpawnActor<ABullet>(m_BulletClass,
							m_ProjectileSpawnPoint->GetComponentLocation(),
							m_ProjectileSpawnPoint->GetComponentRotation());

	//I know that is not the best way to do that, but I've wanted to try it this way.
	UStaticMeshComponent* bulletMesh = bullet->FindComponentByClass<UStaticMeshComponent>();
	bulletMesh->SetMaterial(0, m);
	
	/*
	DrawDebugSphere(GetWorld(),
					m_ProjectileSpawnPoint->GetComponentLocation() + m_ProjectileSpawnPoint->GetForwardVector()*1000.f,
					10.f,
					12,
					FColor::Red,
					false,
					3.f);
	*/
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


