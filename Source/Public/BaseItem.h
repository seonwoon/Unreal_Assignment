#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemInterface.h"
#include "BaseItem.generated.h"

class USphereComponent;

UCLASS()
class MINIPROJECT_API ABaseItem : public AActor, public IItemInterface
{
    GENERATED_BODY()

public:
    ABaseItem();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FName ItemType;
    // ��Ʈ ������Ʈ (��)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
    USceneComponent* Scene;
    // �浹 ������Ʈ (�÷��̾� ���� ���� ������)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
    USphereComponent* Collision;
    // ������ �ð� ǥ���� ����ƽ �޽�
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
    UStaticMeshComponent* StaticMesh;

    virtual void OnItemOverlap(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult) override;
    virtual void OnItemEndOverlap(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex) override;
    virtual void ActivateItem(AActor* Activator) override;
    virtual FName GetItemType() const override;

    void DestroyItem();
};