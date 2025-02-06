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

	// ���� ��ġ ���
	StartLocation = GetActorLocation();
}

void AMovingFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ���� X ��ġ�� �̵��� �Ÿ� ���
	const float CurrentZ = GetActorLocation().Z;
	const float DeltaMovement = MoveSpeed * DeltaTime * MoveDirection;
	float NewZ = CurrentZ + DeltaMovement;

	// ���� ��ġ�κ��� X�� ���� �Ÿ� ���
	const float DistanceFromStart = FMath::Abs(NewZ - StartLocation.Z);
	if (DistanceFromStart > MaxRange)
	{
		// �ʰ��� �Ÿ� ����: �ʰ��� ��ŭ ����, �̵� ���� ����
		const float Overshoot = DistanceFromStart - MaxRange;
		NewZ -= Overshoot * MoveDirection;
		MoveDirection *= -1;
	}

	// Y, Z ��ǥ�� �״�� �����ϸ� X ��ǥ ������Ʈ
	FVector NewLocation = GetActorLocation();
	NewLocation.Z = NewZ;
	SetActorLocation(NewLocation);
}


