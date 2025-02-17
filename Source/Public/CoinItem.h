#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "CoinItem.generated.h"

UCLASS()
class MINIPROJECT_API ACoinItem : public ABaseItem
{
	GENERATED_BODY()

public:
	ACoinItem();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void ActivateItem(AActor* Activator) override;

public:
	// Wave 3 시작 시, 이 함수를 호출하여 코인의 공전(orbit) 모드를 On/Off
	void SetWave3OrbitActive(bool bActive);

protected:
	// 코인의 제자리에서 회전하는 속도 (deg/sec)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
	float SpinSpeed;

	// Wave 3 시 공전 모드 활성화 여부
	bool bOrbitMode;

	// 코인이 스폰된 위치 (공전의 중심점)
	FVector OriginalSpawnLocation;

	// 현재 공전 각도 (단위: degree)
	float OrbitAngle;

	// 공전 반경 (원 중심으로부터의 거리)
	float OrbitRadius;

	// 코인을 획득했을 때 증가하는 점수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
	int32 PointValue;

private:
	// 코인의 자전(Spin) 업데이트 함수
	void UpdateSpin(float DeltaTime);

	// 공전(Orbit) 이동 업데이트 함수 (Orbit 모드 활성 시)
	void UpdateOrbit(float DeltaTime);
};
