// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh"));
	RootComponent = m_BaseMesh;

	m_TrailComponent = CreateDefaultSubobject<UParticleSystemComponent>("Smoke Trail");
	m_TrailComponent->SetupAttachment(RootComponent);
	
	m_ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	m_ProjectileMovementComponent->InitialSpeed = 2000.f;
	m_ProjectileMovementComponent->MaxSpeed = 2400.f;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp,Warning,TEXT("BABA"));
	m_BaseMesh->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
	
}

void ABullet::OnHit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* 
	  otherComp, FVector normalImpulse, const FHitResult& hit)
{
	auto owner = GetOwner();
	if(owner == nullptr)
	{
		Destroy();
		return;	
	}
	auto ownerInstigator = owner->GetInstigatorController();
	auto damageTypeClass = UDamageType::StaticClass();
	if(otherActor && otherActor != this && otherActor != owner)
	{
		//UE_LOG(LogTemp,Warning,TEXT("ANNE"));
		UGameplayStatics::ApplyDamage(otherActor, m_Damage, ownerInstigator, this, damageTypeClass);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_HitParticle, GetActorLocation(), GetActorRotation());
	}
	Destroy();
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



