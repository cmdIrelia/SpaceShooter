// Fill out your copyright notice in the Description page of Project Settings.

#include "BulletController.h"

#include <Components/BoxComponent.h>
#include "EnemyController.h"

// Sets default values
ABulletController::ABulletController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 构建一个默认会出现的Subobject，出现在detail树下面，名字为什么不叫root我也不知道.
	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));

	// 如果没有下面这一句，会出现warning：
	//LogActor: Warning: BP_Bullet_C /Game/Maps/UEDPIE_0_GameMap.GameMap:PersistentLevel.BP_Bullet_C_0 has natively added scene component(s), but none of them were set as the actor's RootComponent - picking one arbitrarily
	//应该是由AShipController调用SpawnActor动态生成导致。
	SetRootComponent(RootBox);

	// 使其能够发生Overlap事件
	RootBox->SetGenerateOverlapEvents(true);

	//链接碰撞以后的回调函数
	RootBox->OnComponentBeginOverlap.AddDynamic(this, &ABulletController::OnOverlap);

}

// Called when the game starts or when spawned
void ABulletController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABulletController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 向上移动
	FVector NewLocation = GetActorLocation();
	NewLocation.X += Speed * DeltaTime;
	SetActorLocation(NewLocation);

	// 超出平板则销毁
	if (NewLocation.X > 600.f) {
		this->Destroy();
		// 打印ActorName
		//FString ActorName = GetName();
	}
}

// Overlap后的回调函数
void ABulletController::OnOverlap(UPrimitiveComponent *OverlapComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(AEnemyController::StaticClass())) {
		//float time = GetWorld()->GetTimeSeconds();
		this->Destroy();
		OtherActor->Destroy();
	}
}
