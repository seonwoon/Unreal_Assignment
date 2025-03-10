#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MiniGameState.generated.h"

class ASpawnVolume;
class ACoinItem;
class AMiniPlayerController;
class UMiniGameInstance;

UCLASS()
class MINIPROJECT_API AMiniGameState : public AGameState
{
	GENERATED_BODY()

public:
	AMiniGameState();

	virtual void BeginPlay() override;

	// Level 관리
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 CurrentLevelIndex;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 MaxLevels;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	TArray<FName> LevelMapNames;

	// Wave 관리
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wave")
	int32 CurrentWaveIndex;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	int32 MaxWaves;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	float WaveDuration;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	TArray<int32> CoinsToSpawnPerWave;

	// Score 및 Coin 관련
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Score")
	int32 Score;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")
	int32 SpawnedCoinCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")
	int32 CollectedCoinCount;

	// Wave 2: 스파이크 트랩 클래스
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave|Hazard")
	TSubclassOf<AActor> SpikeTrapClass;

	// 타이머 핸들
	FTimerHandle WaveTimerHandle;
	FTimerHandle HUDUpdateTimerHandle;

	// Score 관련 함수
	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetScore() const;

	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddScore(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Level")
	void OnGameOver();

	void StartLevel();
	void EndLevel();
	void StartWave();
	void EndWave();
	void OnWaveTimeUp();
	void OnCoinCollected();
	void UpdateHUD();

private:
	// 현재 Wave에 스폰된 아이템들 (Wave 종료 시 파괴)
	UPROPERTY()
	TArray<AActor*> CurrentWaveItems;

	// Wave별 환경 변화 함수
	void EnableWave2Environment();
	void EnableWave3Environment();
	void SetAllCoinsOrbit(bool bActive);

	// 헬퍼 함수들
	ASpawnVolume* GetSpawnVolume() const;
	AMiniPlayerController* GetMiniPlayerController() const;
	UMiniGameInstance* GetMiniGameInstance() const;
};