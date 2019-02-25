// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SpaceShooterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHOOTER_API ASpaceShooterGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Spawning")
	float MINIMUM_INTERVAL = 1.0f;
	
	UPROPERTY(EditAnywhere, Category = "Spawning")
	float MAXIMUM_INTERVAL = 2.0f;

	float TIME_TO_MINIMUM_INTERVAL = 30.0f;

public:

	// 参考其他的类声明成 virtual 和 override
	virtual void BeginPlay() override;

	// 参考其他的类声明成 virtual 和 override
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class AEnemyController> EnemyBlueprint;

	float EnemyTimer;
	float GameTimer;

protected:
	int Score = 0;
};
