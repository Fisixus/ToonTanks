// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
//#include "DrawDebugHelpers.h"

ATank::ATank()
{

	m_SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	m_SpringArmComponent->SetupAttachment(RootComponent);

	m_CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_CameraComponent->SetupAttachment(m_SpringArmComponent);

}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp,Warning,TEXT("SA2"));
	m_PlayerController = Cast<APlayerController>(GetController());
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(m_PlayerController == nullptr) return;
	FHitResult HitResult;
	const bool IsHit = m_PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
	if(IsHit)
	{
		RotateTurret(HitResult.ImpactPoint);
		/*
		DrawDebugSphere(GetWorld(),
		HitResult.ImpactPoint,
		10.f,
		12,
		FColor::Red,
		false,
		-1.f);
		*/
	}
	
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
}



void ATank::Move(float Direction)
{
	auto DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	
	// If no input has been given
	if(FMath::IsWithin(Direction,-0.9f,0.9f))
	{
		m_Speed = FMath::Lerp(m_Speed, 0, DeltaTime*4.f);
	}
	else
	{
		m_Speed = FMath::Lerp(m_Speed, m_Speed + m_Acceleration*Direction, DeltaTime*4.f);
	}
	
	m_Speed = FMath::Clamp(m_Speed,-m_MaxSpeed,m_MaxSpeed);

	FVector NewOffset(0.f);
	NewOffset.X = m_Speed;
	AddActorLocalOffset(NewOffset,true);
}

void ATank::Turn(float Value)
{
	auto DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw =  DeltaTime * m_TurnRate * Value;
	AddActorLocalRotation(DeltaRotation, true);
}
