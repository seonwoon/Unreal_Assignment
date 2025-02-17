
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MiniPawn.generated.h"

UCLASS()
class MINIPROJECT_API AMiniPawn : public APawn
{
	GENERATED_BODY()

public:
	
	AMiniPawn();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
