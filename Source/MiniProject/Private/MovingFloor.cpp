#include "MovingFloor.h"
#include "Math/UnrealMathUtility.h"

AMovingFloor::AMovingFloor()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	SetRootComponent(MeshComponent);

	MoveSpeed = 150.f;
	MaxRange = 100.f;
	MoveDirection = 1;
}

void AMovingFloor::BeginPlay()
{
	Super::BeginPlay();

	// 시작 위치 기록
	StartLocation = GetActorLocation();
}

void AMovingFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 현재 X 위치와 이동할 거리 계산
	const float CurrentZ = GetActorLocation().Z;
	const float DeltaMovement = MoveSpeed * DeltaTime * MoveDirection;
	float NewZ = CurrentZ + DeltaMovement;

	// 시작 위치로부터 X축 기준 거리 계산
	const float DistanceFromStart = FMath::Abs(NewZ - StartLocation.Z);
	if (DistanceFromStart > MaxRange)
	{
		// 초과된 거리 보정: 초과분 만큼 빼고, 이동 방향 반전
		const float Overshoot = DistanceFromStart - MaxRange;
		NewZ -= Overshoot * MoveDirection;
		MoveDirection *= -1;
	}

	// Y, Z 좌표는 그대로 유지하며 X 좌표 업데이트
	FVector NewLocation = GetActorLocation();
	NewLocation.Z = NewZ;
	SetActorLocation(NewLocation);
}


