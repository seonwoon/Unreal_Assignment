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

	// �̵� �ӵ� (����/��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed;

	// �պ� �̵� ���� (�������������� �ִ� �̵� �Ÿ�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MaxRange;

	// ���Ͱ� ���� ���� ������ ��ġ�ߴ� ���� ��ġ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	FVector StartLocation;

	// �̵� ���� (1 �Ǵ� -1)
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	int32 MoveDirection;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
