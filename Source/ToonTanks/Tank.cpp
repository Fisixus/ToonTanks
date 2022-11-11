// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ATank::ATank()
{

	m_SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	m_SpringArmComponent->SetupAttachment(RootComponent);

	m_CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_CameraComponent->SetupAttachment(m_SpringArmComponent);

}