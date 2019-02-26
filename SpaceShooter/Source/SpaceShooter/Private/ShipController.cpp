// Fill out your copyright notice in the Description page of Project Settings.

#include "ShipController.h"

#include <Components/BoxComponent.h>
#include "BulletController.h"
#include <Components/PrimitiveComponent.h>
#include "EnemyController.h"
#include "Kismet/GameplayStatics.h"
#include "SpaceShooterGameMode.h"

// Sets default values
AShipController::AShipController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ����һ��Ĭ�ϻ���ֵ�Subobject��������detail�����棬����Ϊʲô����root��Ҳ��֪��.
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));

	// ָ����
	SetRootComponent(CollisionBox);

	// ʹ���ܹ�����Overlap�¼�
	//CollisionBox->bGenerateOverlapEvents = true;	//����Ȩ�޲���
	CollisionBox->SetGenerateOverlapEvents(true);

	//������ײ�Ժ�Ļص�����
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AShipController::OnOverlap);

	// AutoPossessPlayer ���������Pawn�������Դ���
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Alive at start
	Died = false;

	//Note: OpenLevel��������������Level��ʾ��ȫ��������
	UE_LOG(LogTemp, Warning, TEXT("call AShipController()"));
}

// Called when the game starts or when spawned
void AShipController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShipController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ÿһ�Ķ��ڵ�ǰ��λ����(GetActorLocation)������Input�¼�����ֵ(CurrentVelocity)
	// �������µ�ActorLocation
	if (!CurrentVelocity.IsZero()) {
		FVector NewLocation = GetActorLocation() + Speed*CurrentVelocity*DeltaTime;

		SetActorLocation(NewLocation);
	}

}

// Called to bind functionality to input
void AShipController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// �������¼���ص�������MoveX MoveY����Project Setting��Input�е�����
	PlayerInputComponent->BindAxis("MoveX", this, &AShipController::Move_XAxis);
	PlayerInputComponent->BindAxis("MoveY", this, &AShipController::Move_YAxis);

	// �������
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AShipController::OnShoot);

	//������Ϸ
	PlayerInputComponent->BindAction("Restart", IE_Pressed, this, &AShipController::OnRestart).bExecuteWhenPaused = true;
}

// Move_XAxis
void AShipController::Move_XAxis(float AxisValue)
{
	CurrentVelocity.X = AxisValue * 100.0f;
}

// Move_YAxis
void AShipController::Move_YAxis(float AxisValue)
{
	CurrentVelocity.Y = AxisValue * 100.0f;
}

// OnShoot action
void AShipController::OnShoot()
{
	UWorld *World = GetWorld();

	if (World) {
		FVector Location = GetActorLocation();

		// ����һ���µ�bullet������
		World->SpawnActor<ABulletController>(BulletBlueprint, Location, FRotator::ZeroRotator);
	}
}

// Overlap��Ļص�����
void AShipController::OnOverlap(UPrimitiveComponent *OverlapComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(AEnemyController::StaticClass())) {
		float time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Ship Overlap on %s caused Game Over."), time, *OtherActor->GetName());

		Died = true;
		this->SetActorHiddenInGame(true);

		//��Ϸ����
		((ASpaceShooterGameMode*)GetWorld()->GetAuthGameMode())->OnGameOver();

		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}

void AShipController::OnRestart()
{
	if (Died) {
		// ������ǰLevel
		// ����3��if true options are reset, if false options are carried over from current level
		UGameplayStatics::OpenLevel(this, *GetWorld()->GetName(), false);
		//NOTE: OpenLevel ������ɾ��GameMode��������newһ��.
		//Note: OpenLevel��������������Level��ʾ��ȫ��������.
	}
}
