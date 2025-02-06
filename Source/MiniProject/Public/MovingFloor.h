#pragma once

#include "CoreMinimal.h"
#include "HAL/Platform.h"
#include "GameFramework/Actor.h"
#include "MovingFloor.generated.h"

UCLASS()
class MINIPROJECT_API AMovingFloor : public AActor
{
	GENERATED_BODY()

public:
	AMovingFloor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComponent;

	// 이동 속도 (유닛/초)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed;

	// 왕복 이동 범위 (시작점에서부터 최대 이동 거리)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MaxRange;

	// 액터가 게임 시작 시점에 위치했던 시작 위치
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	FVector StartLocation;

	// 이동 방향 (1 또는 -1)
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	int32 MoveDirection;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
