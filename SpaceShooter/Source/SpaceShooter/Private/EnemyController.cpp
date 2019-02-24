// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyController.h"

#include <Components/BoxComponent.h>

// Sets default values
AEnemyController::AEnemyController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 构建一个默认会出现的Subobject，出现在detail树下面，名字为什么不叫root我也不知道.
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

	// 向下移动(Speed<0)
	FVector NewLocation = GetActorLocation();
	NewLocation.X += Speed * DeltaTime;
	SetActorLocation(NewLocation);

	// 超出平板则销毁
	if (NewLocation.X > 600.f) {
		this->Destroy();
		
		// 打印ActorName
		FString ActorName = GetName();
		UE_LOG(LogTemp, Warning, TEXT("Enemy %s destroyed"), *ActorName);
	}
}

