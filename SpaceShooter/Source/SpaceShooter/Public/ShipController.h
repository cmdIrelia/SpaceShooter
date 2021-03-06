// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ShipController.generated.h"

UCLASS()
class SPACESHOOTER_API AShipController : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShipController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	UShapeComponent *CollisionBox;

	/// 移动相关
	UPROPERTY(EditAnywhere)
	float Speed = 10.0f;

	UPROPERTY(EditAnywhere)
	float XBoard = 650;

	UPROPERTY(EditAnywhere)
	float YBoard = 650;

	// 键盘事件
	void Move_XAxis(float AxisValue);
	// 键盘事件
	void Move_YAxis(float AxisValue);

	FVector CurrentVelocity;

	/// 射击相关
	// 后面要和GetWorld()->SpawnActor联合使用，动态创建对象
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class ABulletController> BulletBlueprint;

	// 键盘事件
	void OnShoot();

	// 填装时间
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	float ReloadTime = 0.5f;

	float LastFireTime = 0;

	/// 碰撞相关
	// 碰撞后GameOver
	bool Died;

	// Overlap后的回调函数
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent *OverlapComponent,
			AActor *OtherActor,
			UPrimitiveComponent *OtherComponent,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult &SweepResult);

	/// 重启游戏
	//键盘事件
	void OnRestart();

};
