#include "MineItem.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

AMineItem::AMineItem()
{
	ExplosionDelay = 5.0f;
	ExplosionRadius = 300.0f;
	ExplosionDamage = 30.0f;
	ItemType = "Mine";

	ExplosionCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionCollision"));
	ExplosionCollision->InitSphereRadius(ExplosionRadius);
	ExplosionCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	ExplosionCollision->SetupAttachment(Scene);
}

void AMineItem::ActivateItem(AActor* Activator)
{
	GetWorld()->GetTimerManager().SetTimer(
		ExplosionTimerHandle,
		this,
		&AMineItem::Explode,
		ExplosionDelay,
		false
	);
}

void AMineItem::Explode()
{
	TArray<AActor*> OverlappingActors;
	ExplosionCollision->GetOverlappingActors(OverlappingActors);

	for (AActor* Actor : OverlappingActors)
	{
		if (Actor && Actor->ActorHasTag("Player"))
		{
			// �������� �߻����� Actor->TakeDamage()�� ����ǵ��� ��
			UGameplayStatics::ApplyDamage(
				Actor,                      // �������� ���� ����
				ExplosionDamage,            // ������ ��
				nullptr,                    // �������� ������ ��ü (���ڸ� ��ġ�� ĳ���Ͱ� �����Ƿ� nullptr)
				this,                       // �������� ������ ������Ʈ(����)
				UDamageType::StaticClass()  // �⺻ ������ ����
			);
		}
	}

	// ���� ���� ���� ������ �ı�
	DestroyItem();
}