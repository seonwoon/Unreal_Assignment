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

	// Level ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 CurrentLevelIndex;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 MaxLevels;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	TArray<FName> LevelMapNames;

	// Wave ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wave")
	int32 CurrentWaveIndex;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	int32 MaxWaves;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	float WaveDuration;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	TArray<int32> CoinsToSpawnPerWave;

	// Score �� Coin ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Score")
	int32 Score;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")
	int32 SpawnedCoinCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")
	int32 CollectedCoinCount;

	// Wave 2: ������ũ Ʈ�� Ŭ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave|Hazard")
	TSubclassOf<AActor> SpikeTrapClass;

	// Ÿ�̸� �ڵ�
	FTimerHandle WaveTimerHandle;
	FTimerHandle HUDUpdateTimerHandle;

	// Score ���� �Լ�
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
	// ���� Wave�� ������ �����۵� (Wave ���� �� �ı�)
	UPROPERTY()
	TArray<AActor*> CurrentWaveItems;

	// Wave�� ȯ�� ��ȭ �Լ�
	void EnableWave2Environment();
	void EnableWave3Environment();
	void SetAllCoinsOrbit(bool bActive);

	// ���� �Լ���
	ASpawnVolume* GetSpawnVolume() const;
	AMiniPlayerController* GetMiniPlayerController() const;
	UMiniGameInstance* GetMiniGameInstance() const;
};