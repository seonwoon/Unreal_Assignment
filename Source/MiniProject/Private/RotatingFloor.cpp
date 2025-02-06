#include "RotatingFloor.h"
#include "Components/StaticMeshComponent.h"

ARotatingFloor::ARotatingFloor()
{
    PrimaryActorTick.bCanEverTick = true;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    SetRootComponent(MeshComponent);

    RotationSpeed = FRotator(0.f, 90.f, 0.f);
}

void ARotatingFloor::BeginPlay()
{
    Super::BeginPlay();
}

void ARotatingFloor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AddActorLocalRotation(RotationSpeed * DeltaTime);
}

