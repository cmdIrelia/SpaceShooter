// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyController.h"

#include <Components/BoxComponent.h>

// Sets default values
AEnemyController::AEnemyController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ����һ��Ĭ�ϻ���ֵ�Subobject��������detail�����棬����Ϊʲô����root��Ҳ��֪��.
	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
}

// Called when the game starts or when spawned
void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �����ƶ�(Speed<0)
	FVector NewLocation = GetActorLocation();
	NewLocation.X += Speed * DeltaTime;
	SetActorLocation(NewLocation);

	// ����ƽ��������
	if (NewLocation.X > 600.f) {
		this->Destroy();
		
		// ��ӡActorName
		FString ActorName = GetName();
		UE_LOG(LogTemp, Warning, TEXT("Enemy %s destroyed"), *ActorName);
	}
}

