// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class TOONTANKS_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* m_BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	class UProjectileMovementComponent* m_ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, Category="General")
	UParticleSystem* m_HitParticle;

	UPROPERTY(VisibleAnywhere, Category="General")
	UParticleSystemComponent* m_TrailComponent;

	UPROPERTY(EditAnywhere, Category="General")
	TSubclassOf<class UCameraShakeBase> m_HitCamShakeClass;

	UPROPERTY(EditAnywhere)
	float m_Damage = 10.f;
	
	UFUNCTION(BlueprintCallable)
		virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* 
		  OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
};
