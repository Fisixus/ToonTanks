// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	m_CurrentHealth = m_MaxHealth;
	//UE_LOG(LogTemp, Warning, TEXT("ZAA"));
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	m_ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
}


void UHealthComponent::DamageTaken(AActor* damagedActor, float damage, const UDamageType* damageType,
	AController* instigator, AActor* damageCauser)
{
	if(damage <= 0.f) return;
	m_CurrentHealth -= damage;
	UE_LOG(LogTemp, Warning, TEXT("%s HEALTH:%f"),*damagedActor->GetName(),m_CurrentHealth);
	if(m_CurrentHealth <= 0 && m_ToonTanksGameMode)
	{
		m_ToonTanksGameMode->ActorDied(damagedActor);
	}
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



