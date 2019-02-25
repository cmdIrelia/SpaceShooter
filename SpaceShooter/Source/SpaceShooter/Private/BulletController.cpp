// Fill out your copyright notice in the Description page of Project Settings.

#include "BulletController.h"

#include <Components/BoxComponent.h>
#include "EnemyController.h"

// Sets default values
ABulletController::ABulletController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ����һ��Ĭ�ϻ���ֵ�Subobject��������detail�����棬����Ϊʲô����root��Ҳ��֪��.
	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));

	// ���û��������һ�䣬�����warning��
	//LogActor: Warning: BP_Bullet_C /Game/Maps/UEDPIE_0_GameMap.GameMap:PersistentLevel.BP_Bullet_C_0 has natively added scene component(s), but none of them were set as the actor's RootComponent - picking one arbitrarily
	//Ӧ������AShipController����SpawnActor��̬���ɵ��¡�
	SetRootComponent(RootBox);

	// ʹ���ܹ�����Overlap�¼�
	RootBox->SetGenerateOverlapEvents(true);

	//������ײ�Ժ�Ļص�����
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

	// �����ƶ�
	FVector NewLocation = GetActorLocation();
	NewLocation.X += Speed * DeltaTime;
	SetActorLocation(NewLocation);

	// ����ƽ��������
	if (NewLocation.X > 600.f) {
		this->Destroy();
		// ��ӡActorName
		//FString ActorName = GetName();
	}
}

// Overlap��Ļص�����
void ABulletController::OnOverlap(UPrimitiveComponent *OverlapComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(AEnemyController::StaticClass())) {
		//float time = GetWorld()->GetTimeSeconds();
		this->Destroy();
		OtherActor->Destroy();
	}
}
