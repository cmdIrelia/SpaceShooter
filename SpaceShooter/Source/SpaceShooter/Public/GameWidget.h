// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

// UMG��ͷ�ļ�
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
	
	/// ������ʾ
	UPROPERTY()
	UTextBlock *ScoreText;

	void SetScore(int score);
	void OnGameOver(int score);

	/// ��װ״̬��ʾ
	UPROPERTY()
	UTextBlock *LoadStateText;

	void SetLoadingState();
	void LoadFinished();

	// ʱ����ʾ
	UPROPERTY()
	UTextBlock *LiveTimeText;
	void SetTime(float time);
};
