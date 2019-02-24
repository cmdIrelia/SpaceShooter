// Fill out your copyright notice in the Description page of Project Settings.

#include "BulletController.h"

#include <Components/BoxComponent.h>

// Sets default values
ABulletController::ABulletController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ����һ��Ĭ�ϻ���ֵ�Subobject��������detail�����棬����Ϊʲô����root��Ҳ��֪��.
	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));

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

	// �����ƶ�
	FVector NewLocation = GetActorLocation();
	NewLocation.X += Speed * DeltaTime;
	SetActorLocation(NewLocation);

	// ����ƽ��������
	if (NewLocation.X > 600.f) {
		this->Destroy();

		// ��ӡActorName
		FString ActorName = GetName();
		UE_LOG(LogTemp, Warning, TEXT("Bullet %s destroyed"), *ActorName);
	}
}
