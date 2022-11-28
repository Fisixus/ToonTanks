// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void HandleDestruction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void RotateTurret(FVector LookAtTarget, float turnInterpSpeed=15.f) const;
	void Fire(UMaterialInterface* m);//TODO: Change bullet colors

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	class UCapsuleComponent* m_CapsuleComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* m_BaseMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* m_TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	USceneComponent* m_ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category="General")
	TSubclassOf<class ABullet> m_BulletClass;

	UPROPERTY(EditAnywhere, Category="General")
	UParticleSystem* m_DeathParticle;

	UPROPERTY(EditAnywhere, Category="General")
	TSubclassOf<class UCameraShakeBase> m_DeathCamShakeClass;
};
