// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletController.generated.h"

UCLASS()
class SPACESHOOTER_API ABulletController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	UShapeComponent *RootBox;

	/// 运动相关
	UPROPERTY(EditDefaultsOnly)
	float Speed = 400.0f;

	UPROPERTY(EditDefaultsOnly)
	float YBoard = 650;

	UPROPERTY(EditDefaultsOnly)
	float XBoard = 650;

	/// 碰撞相关
	// Overlap后的回调函数
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent *OverlapComponent,
			AActor *OtherActor,
			UPrimitiveComponent *OtherComponent,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult &SweepResult);
};
