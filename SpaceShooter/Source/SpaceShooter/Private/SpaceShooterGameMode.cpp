// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShooterGameMode.h"

#include "EnemyController.h"

void ASpaceShooterGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ASpaceShooterGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GameTimer += DeltaTime;
	EnemyTimer -= DeltaTime;

	if (EnemyTimer <= 0.f) {
		float difficultyPercentage = FMath::Min(GameTimer / MINIMUM_INTERVAL, 1.0f);
		EnemyTimer = MAXIMUM_INTERVAL - (MAXIMUM_INTERVAL - MINIMUM_INTERVAL)*difficultyPercentage;

		UWorld *World = GetWorld();
		if (World) {
			FVector Location = FVector(600.f, FMath::RandRange(-800.f, 800.f), 70.f);
			World->SpawnActor<AEnemyController>(EnemyBlueprint, Location, FRotator::ZeroRotator);
		}
	}
}
