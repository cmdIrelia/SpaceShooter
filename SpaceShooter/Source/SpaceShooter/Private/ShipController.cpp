// Fill out your copyright notice in the Description page of Project Settings.

#include "ShipController.h"

#include <Components/BoxComponent.h>

// Sets default values
AShipController::AShipController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ����һ��Ĭ�ϻ���ֵ�Subobject��������detail�����棬���ֽ�root.
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));

	// AutoPossessPlayer ���������Pawn�������Դ���
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AShipController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShipController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ÿһ�Ķ��ڵ�ǰ��λ����(GetActorLocation)������Input�¼�����ֵ(CurrentVelocity)
	// �������µ�ActorLocation
	if (!CurrentVelocity.IsZero()) {
		FVector NewLocation = GetActorLocation() + Speed*CurrentVelocity*DeltaTime;

		SetActorLocation(NewLocation);
	}

}

// Called to bind functionality to input
void AShipController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// �������¼���ص�������MoveX MoveY����Project Setting��Input�е�����
	PlayerInputComponent->BindAxis("MoveX", this, &AShipController::Move_XAxis);
	PlayerInputComponent->BindAxis("MoveY", this, &AShipController::Move_YAxis);
}

// Move_XAxis
void AShipController::Move_XAxis(float AxisValue)
{
	CurrentVelocity.X = AxisValue * 100.0f;
}

// Move_YAxis
void AShipController::Move_YAxis(float AxisValue)
{
	CurrentVelocity.Y = AxisValue * 100.0f;
}