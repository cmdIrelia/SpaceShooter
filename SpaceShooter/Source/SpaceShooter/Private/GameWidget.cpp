// Fill out your copyright notice in the Description page of Project Settings.

#include "GameWidget.h"

void UGameWidget::Load()
{
	/// 计分板
	const FName TextBlockName = FName(TEXT("GameTextBlock"));

	if (ScoreText == nullptr) {
		ScoreText = (UTextBlock*)(WidgetTree->FindWidget(TextBlockName));
	}

	/// 填装状态指示
	const FName LoadStateTextBlockName = FName(TEXT("LoadState"));
	if (LoadStateText == nullptr) {
		LoadStateText = (UTextBlock*)(WidgetTree->FindWidget(LoadStateTextBlockName));
	}

	/// 游戏时间指示
	const FName LiveTimeTextBlockName = FName(TEXT("LiveTime"));
	if (LiveTimeText == nullptr) {
		LiveTimeText = (UTextBlock*)(WidgetTree->FindWidget(LiveTimeTextBlockName));
	}
}

void UGameWidget::SetScore(int score)
{
	if (ScoreText != nullptr) {
		ScoreText->SetText(FText::FromString(FString(TEXT("Score: ")) + FString::FromInt(score)));
	}
}

void UGameWidget::OnGameOver(int score)
{
	if (ScoreText != nullptr) {
		ScoreText->SetText(FText::FromString(
			FString(TEXT("Score: ")) +
			FString::FromInt(score) +
			FString(TEXT("\nPress R to Restart.")))
		);
	}
}

void UGameWidget::SetLoadingState()
{
	if (LoadStateText != nullptr) {
		LoadStateText->SetText(FText::FromString(FString(TEXT("Reloading"))));
		LoadStateText->SetColorAndOpacity(FSlateColor(FLinearColor(1, 0.1, 0.1)));
	}
}

void UGameWidget::LoadFinished()
{
	if (LoadStateText != nullptr) {
		LoadStateText->SetText(FText::FromString(FString(TEXT("Ready!"))));
		LoadStateText->SetColorAndOpacity(FSlateColor(FLinearColor(0.1, 1, 0.1)));
	}
}

void UGameWidget::SetTime(float time)
{
	if (LiveTimeText != nullptr) {
		LiveTimeText->SetText(FText::FromString(FString::Printf(TEXT("Go Bro!\n%.2f"),time)));
		LiveTimeText->SetColorAndOpacity(FSlateColor(FLinearColor(FMath::Clamp<float>(60.f/time,0,1), 0.1, 0.1)));
	}
}
