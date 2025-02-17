#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MiniCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
struct FInputActionValue;

UCLASS()
class MINIPROJECT_API AMiniCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AMiniCharacter();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    USpringArmComponent* SpringArmComp;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    UCameraComponent* CameraComp;

    // ���� ü���� �������� �Լ�
    UFUNCTION(BlueprintPure, Category = "Health")
    float GetHealth() const;
    // ü���� ȸ����Ű�� �Լ�
    UFUNCTION(BlueprintCallable, Category = "Health")
    void AddHealth(float Amount); 

protected:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION()
    void Move(const FInputActionValue& value);
    UFUNCTION()
    void StartJump(const FInputActionValue& value);
    UFUNCTION()
    void StopJump(const FInputActionValue& value);
    UFUNCTION()
    void Look(const FInputActionValue& value);
    UFUNCTION()
    void StartSprint(const FInputActionValue& value);
    UFUNCTION()
    void StopSprint(const FInputActionValue& value);

    // �ִ� ü��
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    float MaxHealth;
    // ���� ü��
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
    float Health;
    // ��� ó�� �Լ� (ü���� 0 ���ϰ� �Ǿ��� �� ȣ��)
    UFUNCTION(BlueprintCallable, Category = "Health")
    virtual void OnDeath();

    // ������ ó�� �Լ� - �ܺηκ��� �������� ���� �� ȣ���
// �Ǵ� AActor�� TakeDamage()�� �������̵�
    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
    float NormalSpeed;
    float SprintSpeedMultiplier;
    float SprintSpeed;
};