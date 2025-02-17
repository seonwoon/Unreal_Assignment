#include "CoinItem.h"
#include "MiniGameState.h"
#include "Engine/World.h"

ACoinItem::ACoinItem()
	: SpinSpeed(180.f)
	, bOrbitMode(false)
	, OrbitAngle(0.f)
	, OrbitRadius(100.f)
	, PointValue(10)
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACoinItem::BeginPlay()
{
	Super::BeginPlay();

	// 코인이 스폰된 위치를 공전의 중심점으로 저장
	OriginalSpawnLocation = GetActorLocation();
}

void ACoinItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateSpin(DeltaTime);

	if (bOrbitMode)
	{
		UpdateOrbit(DeltaTime);
	}
}

void ACoinItem::UpdateSpin(float DeltaTime)
{
	// 코인을 Yaw축 기준으로 회전시킴
	AddActorLocalRotation(FRotator(0.f, SpinSpeed * DeltaTime, 0.f));
}

void ACoinItem::UpdateOrbit(float DeltaTime)
{
	// OrbitSpeed는 100 deg/sec (필요 시 속성으로 분리 가능)
	const float OrbitSpeed = 100.f;
	OrbitAngle += OrbitSpeed * DeltaTime;

	// 각도를 라디안 단위로 변환
	const float Radians = FMath::DegreesToRadians(OrbitAngle);

	// 원의 방정식을 이용하여 X/Y 위치 계산 (Z는 고정)
	FVector NewPosition = OriginalSpawnLocation;
	NewPosition.X += OrbitRadius * FMath::Cos(Radians);
	NewPosition.Y += OrbitRadius * FMath::Sin(Radians);

	SetActorLocation(NewPosition);
}

void ACoinItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);

	// 플레이어가 코인을 획득한 경우
	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (UWorld* World = GetWorld())
		{
			if (AMiniGameState* GameState = World->GetGameState<AMiniGameState>())
			{
				GameState->AddScore(PointValue);
				GameState->OnCoinCollected();
			}
		}
		DestroyItem();
	}
}

void ACoinItem::SetWave3OrbitActive(bool bActive)
{
	bOrbitMode = bActive;
}
