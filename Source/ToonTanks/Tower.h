// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	class ATank* m_Tank;

	UPROPERTY(EditDefaultsOnly, Category = "General")
	float m_MinLocationDistance = 300.f;

	FTimerHandle m_FireRateTimerHandle;
	FVector2d m_FireGap = FVector2d(2.f,4.f);
	void CheckFireCondition();

	bool IsInFireRange() const;
};
