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
	ASpaceShooterGameMode();

	~ASpaceShooterGameMode();

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

	// 生成Enemies  UPROPERTY可以修改变量值
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class AEnemyController> EnemyBlueprint;

	float EnemyTimer;
	float GameTimer;

	// 生成UI  UFUNCTION+BlueprintCallable可以传参进来
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void ChangeMenuWidget(TSubclassOf<class UUserWidget> NewWidgetClass);

	void IncrementScore();
	void OnGameOver();

protected:
	int Score = 0;

	// UI相关 暴露给蓝图 NOTE:生成的类中，大量的使用了TSubclassOf
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<class UUserWidget> StartingWidgetClass;

	UPROPERTY()
	UUserWidget *CurrentWidget;
};
