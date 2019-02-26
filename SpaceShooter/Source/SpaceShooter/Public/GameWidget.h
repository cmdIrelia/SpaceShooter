// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

// UMG的头文件
#include "UMG.h"
#include "UMGStyle.h"
#include "IUMGModule.h"
#include "Slate/SObjectWidget.h"


#include "GameWidget.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHOOTER_API UGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void Load();
	
	/// 分数显示
	UPROPERTY()
	UTextBlock *ScoreText;

	void SetScore(int score);
	void OnGameOver(int score);

	/// 填装状态显示
	UPROPERTY()
	UTextBlock *LoadStateText;

	void SetLoadingState();
	void LoadFinished();

	// 时间显示
	UPROPERTY()
	UTextBlock *LiveTimeText;
	void SetTime(float time);
};
