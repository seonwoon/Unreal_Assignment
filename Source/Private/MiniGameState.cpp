#include "MiniGameState.h"
#include "MiniGameInstance.h"
#include "MiniPlayerController.h"
#include "SpawnVolume.h"
#include "CoinItem.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"

AMiniGameState::AMiniGameState()
	: Score(0)
	, SpawnedCoinCount(0)
	, CollectedCoinCount(0)
	, CurrentLevelIndex(0)
	, MaxLevels(3)
	, CurrentWaveIndex(0)
	, MaxWaves(3)
	, WaveDuration(20.f)
	, CoinsToSpawnPerWave({ 20, 30, 40 })
	, SpikeTrapClass(nullptr)
{
}

void AMiniGameState::BeginPlay()
{
	Super::BeginPlay();

	StartLevel();

	GetWorldTimerManager().SetTimer(
		HUDUpdateTimerHandle,
		this,
		&AMiniGameState::UpdateHUD,
		0.1f,
		true
	);
}

int32 AMiniGameState::GetScore() const
{
	return Score;
}

void AMiniGameState::AddScore(int32 Amount)
{
	if (UMiniGameInstance* MiniGameInstance = GetMiniGameInstance())
	{
		MiniGameInstance->AddToScore(Amount);
	}
}

void AMiniGameState::StartLevel()
{
	if (AMiniPlayerController* MiniPlayerController = GetMiniPlayerController())
	{
		MiniPlayerController->ShowGameHUD();
	}

	if (UMiniGameInstance* MiniGameInstance = GetMiniGameInstance())
	{
		CurrentLevelIndex = MiniGameInstance->CurrentLevelIndex;
	}

	CurrentWaveIndex = 0;
	StartWave();
}

void AMiniGameState::StartWave()
{
	// 1. 코인 카운트 초기화 및 이전 Wave 아이템 제거
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;
	for (AActor* Item : CurrentWaveItems)
	{
		if (Item && Item->IsValidLowLevelFast())
		{
			Item->Destroy();
		}
	}
	CurrentWaveItems.Empty();

	// 2. 이번 Wave에 스폰할 코인 개수 결정
	int32 CoinsToSpawn = (CoinsToSpawnPerWave.IsValidIndex(CurrentWaveIndex)) ? CoinsToSpawnPerWave[CurrentWaveIndex] : 20;

	// 3. SpawnVolume을 이용해 코인 스폰
	if (ASpawnVolume* SpawnVolume = GetSpawnVolume())
	{
		for (int32 i = 0; i < CoinsToSpawn; i++)
		{
			if (AActor* SpawnedActor = SpawnVolume->SpawnRandomItem())
			{
				if (SpawnedActor->IsA(ACoinItem::StaticClass()))
				{
					SpawnedCoinCount++;
					CurrentWaveItems.Add(SpawnedActor);
				}
			}
		}
	}

	// 4. Wave별 환경 변화
	if (CurrentWaveIndex == 1)
	{
		EnableWave2Environment();
	}
	else if (CurrentWaveIndex == 2)
	{
		EnableWave3Environment();
	}

	// 5. Wave 타이머 시작 (WaveDuration 후 OnWaveTimeUp 호출)
	GetWorldTimerManager().SetTimer(
		WaveTimerHandle,
		this,
		&AMiniGameState::OnWaveTimeUp,
		WaveDuration,
		false
	);
}

void AMiniGameState::EndWave()
{
	// 남은 Wave 타이머 제거
	GetWorldTimerManager().ClearTimer(WaveTimerHandle);

	// Wave3에서 활성화한 코인 궤도 회전 비활성화
	if (CurrentWaveIndex == 2)
	{
		SetAllCoinsOrbit(false);
	}

	// 다음 Wave 진행 또는 Level 종료
	++CurrentWaveIndex;
	if (CurrentWaveIndex >= MaxWaves)
	{
		EndLevel();
	}
	else
	{
		StartWave();
	}
}

void AMiniGameState::OnWaveTimeUp()
{
	EndWave();
}

void AMiniGameState::OnCoinCollected()
{
	CollectedCoinCount++;
	UE_LOG(LogTemp, Warning, TEXT("Coin Collected: %d / %d"), CollectedCoinCount, SpawnedCoinCount);

	if (SpawnedCoinCount > 0 && CollectedCoinCount >= SpawnedCoinCount)
	{
		EndWave();
	}
}

void AMiniGameState::EndLevel()
{
	GetWorldTimerManager().ClearTimer(WaveTimerHandle);

	if (UMiniGameInstance* SpartaGameInstance = GetMiniGameInstance())
	{
		AddScore(Score);
		CurrentLevelIndex++;
		MiniGameInstance->CurrentLevelIndex = CurrentLevelIndex;

		if (CurrentLevelIndex >= MaxLevels)
		{
			OnGameOver();
			return;
		}

		if (LevelMapNames.IsValidIndex(CurrentLevelIndex))
		{
			UGameplayStatics::OpenLevel(GetWorld(), LevelMapNames[CurrentLevelIndex]);
		}
		else
		{
			OnGameOver();
		}
	}
}

void AMiniGameState::OnGameOver()
{
	if (AMiniPlayerController* MiniPlayerController = GetMiniPlayerController())
	{
		MiniPlayerController->SetPause(true);
		MiniPlayerController->ShowMainMenu(true);
	}
}

void AMiniGameState::UpdateHUD()
{
	if (AMiniPlayerController* MiniPlayerController = GetMiniPlayerController())
	{
		if (UUserWidget* HUDWidget = MiniPlayerController->GetHUDWidget())
		{
			// 남은 시간 업데이트
			if (UTextBlock* TimeText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Time"))))
			{
				float RemainingTime = GetWorldTimerManager().GetTimerRemaining(WaveTimerHandle);
				TimeText->SetText(FText::FromString(FString::Printf(TEXT("Time: %.1f"), RemainingTime)));
			}

			// Score 업데이트
			if (UTextBlock* ScoreText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Score"))))
			{
				if (UMiniGameInstance* MiniGameInstance = GetMiniGameInstance())
				{
					ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), SpartaGameInstance->TotalScore)));
				}
			}

			// Wave 업데이트
			if (UTextBlock* WaveText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Wave"))))
			{
				WaveText->SetText(FText::FromString(FString::Printf(TEXT("Wave: %d / %d"), CurrentWaveIndex + 1, MaxWaves)));
			}

			// Level 업데이트
			if (UTextBlock* LevelText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Level"))))
			{
				LevelText->SetText(FText::FromString(FString::Printf(TEXT("Level: %d"), CurrentLevelIndex + 1)));
			}
		}
	}
}



void AMiniGameState::EnableWave3Environment()
{
	SetAllCoinsOrbit(true);
}

void AMiniGameState::SetAllCoinsOrbit(bool bActive)
{
	TArray<AActor*> AllCoins;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACoinItem::StaticClass(), AllCoins);

	for (AActor* CoinActor : AllCoins)
	{
		if (ACoinItem* Coin = Cast<ACoinItem>(CoinActor))
		{
			Coin->SetWave3OrbitActive(bActive);
		}
	}
}

ASpawnVolume* AMiniGameState::GetSpawnVolume() const
{
	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);
	return (FoundVolumes.Num() > 0) ? Cast<ASpawnVolume>(FoundVolumes[0]) : nullptr;
}

AMiniPlayerController* AMiniGameState::GetMiniPlayerController() const
{
	return Cast<AMiniPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

UMiniGameInstance* AMiniGameState::GetMiniGameInstance() const
{
	return Cast<UMiniGameInstance>(GetGameInstance());
}
