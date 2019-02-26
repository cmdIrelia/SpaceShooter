// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShooterGameMode.h"

#include "EnemyController.h"
#include "GameWidget.h"

ASpaceShooterGameMode::ASpaceShooterGameMode()
{
	//NOTE: OpenLevel 操作会删除GameMode并且重新new一个.
	UE_LOG(LogTemp, Warning, TEXT("ASpaceShooterGameMode()"));
}

ASpaceShooterGameMode::~ASpaceShooterGameMode()
{
	UE_LOG(LogTemp, Warning, TEXT("delete ASpaceShooterGameMode()"));
}


void ASpaceShooterGameMode::BeginPlay()
{
	Super::BeginPlay();

	// 将显示的Widget修改为BP中的StartingWidgetClass
	ChangeMenuWidget(StartingWidgetClass);

	// cast
	((UGameWidget*)CurrentWidget)->Load();

	UE_LOG(LogTemp, Warning, TEXT("ASpaceShooterGameMode BeginPlay()"));
}

void ASpaceShooterGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GameTimer += DeltaTime;
	EnemyTimer -= DeltaTime;

	if (EnemyTimer <= 0.f) {

		// Don't know why.
		float difficultyPercentage = FMath::Min(GameTimer / MINIMUM_INTERVAL, 1.f);
		EnemyTimer = MAXIMUM_INTERVAL - (MAXIMUM_INTERVAL - MINIMUM_INTERVAL)*difficultyPercentage;
		//UE_LOG(LogTemp, Warning, TEXT("EnemyTimer on SpawnActor: %f"), EnemyTimer);
		
		UWorld *World = GetWorld();
		if (World) {
			FVector Location = FVector(600.f, FMath::RandRange(-800.f, 800.f), 70.f);
			World->SpawnActor<AEnemyController>(EnemyBlueprint, Location, FRotator::ZeroRotator);
		}
	}
}

void ASpaceShooterGameMode::ChangeMenuWidget(TSubclassOf<class UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr) {
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}

	if (NewWidgetClass != nullptr) {
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);

		if (CurrentWidget != nullptr) {
			CurrentWidget->AddToViewport();
		}
	}
}

void ASpaceShooterGameMode::IncrementScore()
{
	Score += 100;
	((UGameWidget*)CurrentWidget)->SetScore(Score);

}

void ASpaceShooterGameMode::OnGameOver()
{
	((UGameWidget*)CurrentWidget)->OnGameOver(Score);
}
