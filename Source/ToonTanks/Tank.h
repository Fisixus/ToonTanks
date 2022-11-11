// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
public:
	ATank();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	class USpringArmComponent* m_SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	class UCameraComponent* m_CameraComponent;


	UPROPERTY(VisibleAnywhere, Category = "Movement")
	float m_Speed = 0.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float m_MaxSpeed = 450.5f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float m_Acceleration = 40.f;

	void Move(float Value);
};
