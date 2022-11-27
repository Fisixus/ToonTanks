// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	void ActorDied(AActor* deadActor);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);
	
private:
	class ATank* m_Tank;
	class AToonTanksPlayerController* m_ToonTanksPlayerController;

	UPROPERTY(EditDefaultsOnly, Category="General")
	float m_startDelay = 3.f;

	void HandleGameStart();

	uint32_t m_TowerCount = 0;
	uint32_t FindTotalTowerCount();
};
