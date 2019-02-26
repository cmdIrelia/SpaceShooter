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

	// �ο��������������� virtual �� override
	virtual void BeginPlay() override;

	// �ο��������������� virtual �� override
	virtual void Tick(float DeltaTime) override;

	// ����Enemies  UPROPERTY�����޸ı���ֵ
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class AEnemyController> EnemyBlueprint;

	float EnemyTimer;
	float GameTimer;

	// ����UI  UFUNCTION+BlueprintCallable���Դ��ν���
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void ChangeMenuWidget(TSubclassOf<class UUserWidget> NewWidgetClass);

	void IncrementScore();
	void OnGameOver();

protected:
	int Score = 0;

	// UI��� ��¶����ͼ NOTE:���ɵ����У�������ʹ����TSubclassOf
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<class UUserWidget> StartingWidgetClass;

	UPROPERTY()
	UUserWidget *CurrentWidget;
};
