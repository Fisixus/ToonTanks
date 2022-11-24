// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();
	m_Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
	GetWorldTimerManager().SetTimer(m_FireRateTimerHandle, this,
		&ATower::CheckFireCondition, FMath::RandRange(m_FireGap.X,m_FireGap.Y), false);
}

void ATower::CheckFireCondition()
{
	if(IsInFireRange())
	{
		Fire();
	}
	
	GetWorldTimerManager().SetTimer(m_FireRateTimerHandle, this, &ATower::CheckFireCondition,
		FMath::RandRange(m_FireGap.X,m_FireGap.Y), false);
}

bool ATower::IsInFireRange() const
{
	if(m_Tank)
	{
		float distance = FVector::Dist(GetActorLocation(), m_Tank->GetActorLocation());
		if(distance <= m_MinLocationDistance)
		{
			return true;
		}
	}
	return false;
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (IsInFireRange())
	{
		RotateTurret(m_Tank->GetActorLocation(), 5.f);
	}
}


