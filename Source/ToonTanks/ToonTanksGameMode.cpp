// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"

#include "Tank.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	m_Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
}

void AToonTanksGameMode::ActorDied(AActor* deadActor)
{
	if(deadActor == m_Tank)
	{
		m_Tank->HandleDestruction();
		auto pController = m_Tank->GetPlayerController();
		if(pController != nullptr)
		{
			m_Tank->DisableInput(pController);
			pController->bShowMouseCursor = false;
		}
	}
	else if(ATower* destroyedTower = Cast<ATower>(deadActor))
	{
		destroyedTower->HandleDestruction();
	}
}


