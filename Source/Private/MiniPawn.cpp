

#include "MiniPawn.h"


AMiniPawn::AMiniPawn()
{
 
	PrimaryActorTick.bCanEverTick = true;

}


void AMiniPawn::BeginPlay()
{
	Super::BeginPlay();
	
}


void AMiniPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMiniPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

