// Fill out your copyright notice in the Description page of Project Settings.

#include "ShipController.h"

#include <Components/BoxComponent.h>
#include "BulletController.h"
#include <Components/PrimitiveComponent.h>
#include "EnemyController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AShipController::AShipController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 构建一个默认会出现的Subobject，出现在detail树下面，名字为什么不叫root我也不知道.
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	
	//CollisionBox->bGenerateOverlapEvents = true;	//访问权限不对
	CollisionBox->SetGenerateOverlapEvents(true);
	//链接碰撞以后的回调函数
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AShipController::OnOverlap);

	// AutoPossessPlayer 这个变量是Pawn类里面自带的
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	UE_LOG(LogTemp, Warning, TEXT("AShipController()"))
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

	// 每一拍都在当前的位置上(GetActorLocation)，根据Input事件输入值(CurrentVelocity)
	// 来设置新的ActorLocation
	if (!CurrentVelocity.IsZero()) {
		FVector NewLocation = GetActorLocation() + Speed*CurrentVelocity*DeltaTime;

		SetActorLocation(NewLocation);
	}

}

// Called to bind functionality to input
void AShipController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 绑定输入事件与回调函数，MoveX MoveY是在Project Setting的Input中的名字
	PlayerInputComponent->BindAxis("MoveX", this, &AShipController::Move_XAxis);
	PlayerInputComponent->BindAxis("MoveY", this, &AShipController::Move_YAxis);

	// 射击动作
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AShipController::OnShoot);
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

		// 创建一个新的bullet对象了
		World->SpawnActor<ABulletController>(BulletBlueprint, Location, FRotator::ZeroRotator);
	}
}

// Overlap后的回调函数
void AShipController::OnOverlap(UPrimitiveComponent *OverlapComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	float time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: Overlap Event."),time)

	if (OtherActor->IsA(AEnemyController::StaticClass())) {
		Died = true;
		this->SetActorHiddenInGame(true);

		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}
