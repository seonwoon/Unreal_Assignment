#include "BigCoinItem.h"

ABigCoinItem::ABigCoinItem()
{
    // ���� CoinItem�� PointValue�� 50���� �����
    PointValue = 50;
    ItemType = "BigCoin";
}

void ABigCoinItem::ActivateItem(AActor* Activator)
{
    // �θ��� �⺻ ���� ȹ�� ���� ���
    Super::ActivateItem(Activator);

    // �� ���θ��� �߰� ����(����Ʈ, ���� ��� ��)�� ���⼭ �߰��� �� ����
}