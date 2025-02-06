#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingFloor.generated.h"

UCLASS()
class MINIPROJECT_API ARotatingFloor : public AActor
{
    GENERATED_BODY()
public:
    ARotatingFloor();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* MeshComponent;

    // �� ������ ȸ�� �ӵ�
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
    FRotator RotationSpeed;

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
};