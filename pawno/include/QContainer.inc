//====================================== Qoo Container Core =======================================
//
//											Version: 2.0
//											Made by Qoo
//
//=================================================================================================

#if defined _QContainer_included
	#endinput
#endif
#define _QContainer_included
#pragma library QContainer

/*������ ������. ���� �迭 ũ�Ⱑ 20�̶�� ���� ��� 40���� �迭ũ�Ⱚ�� 20���� �������� ������. �ֳ��ϸ� ������ �迭 �� ���������� �迭 ũ��� �迭���� ��ġ���� �˻��ϱ� ����.
������ �迭 ũ�� - 1���� ���� �� �����.*/
#define CreateContainer(%0,%1) new QContainer: %0[%1 + 1] = { QContainer: (%1 * 2), QContainer: (%1 * 2 - 1), ... }

#define CONTAINER_SIZE CONTAINER_ARRAY_SIZE
#define CONTAINER_ARRAY_SIZE(%0) sizeof(%0) - 1

/*�ش� ���� ������ִ��� Ȯ��. �ش� ������ �����ϴ� �ε����� ���� ���� �迭 ũ�� - 1�̶�� �ش� ���� �������� �� ���̹Ƿ� ���̰�,
���� �迭 ũ�� - 1���� �۴ٸ� ���� �� ������ �ڿ� ���� �� �ִٴ� ���� �ǹ��ϹǷ� ���̰�,
���� �迭 ũ�� - 1���� ũ�ٸ� �ش� ���� ���� �ʾҴٴ� ���� �ǹ��ϹǷ� ����*/
#define IsValidContainerData(%0,%1) (%1 >= 0 && %1 < CONTAINER_ARRAY_SIZE(%0) && _: %0[%1] <= CONTAINER_ARRAY_SIZE(%0))

// ���� �ݺ���. �ּ� ���÷δ� (new i : playerList) Ȥ�� (i : playerList) (��)�� ������.
#define contloop(%0) for (new QCONTAINER_CONTLOOP_1|||QCONTAINER_CONTLOOP_2|||%0|||)

/*new�� ���͸� ��.
���� ó�� contloop�� ������� new QCONTAINER_CONTLOOP_1|||QCONTAINER_CONTLOOP_2|||i:playerList|||�� ������
QCONTAINER_CONTLOOP_2|||QCONTAINER_CONTLOOP_1|||i:playerList|||�� ��ȯ�ǰ�,

���� QCONTAINER_CONTLOOP_2(��)�� �����ϴ� ��ũ�η� ������� new i=QCONTAINER_CONTLOOP_4|||QCONTAINER_CONTLOOP_3|||new i:playerList|||�� ������
QCONTAINER_CONTLOOP_3|||i=QCONTAINER_CONTLOOP_4|||new i|||playerList|||�� ��ȯ�Ǿ�
QCONTAINER_CONTLOOP_3�� �����ϴ� ��ũ�ΰ� ȣ���.

���� QCONTAINER_CONTLOOP_3(��)�� �����ϴ� ��ũ�η� ������� new QCONTAINER_CONTLOOP_5;Player: i|||QCONTAINER_CONTLOOP_6|||playerList|||�� ������
QCONTAINER_CONTLOOP_6|||QCONTAINER_CONTLOOP_5;i|||*/
#define new%0|||%1|||%2:%3||| %1|||%0|||%2|||%3|||

/*���� new�� ���� �ٷ� ���������� �����ϸ�
i=QCONTAINER_CONTLOOP_4|||QCONTAINER_CONTLOOP_3|||i:playerList||| �̷��� ��ȯ�ǰ�,
QCONTAINER_CONTLOOP_4(��)�� �����ϴ� ��ũ�ΰ� �ٷ� ȣ��Ǿ� �ݺ����� �ϼ���.

�׷��� �ʰ� 'new ������'���� �����ϸ� new i=QCONTAINER_CONTLOOP_4|||QCONTAINER_CONTLOOP_3|||new i:playerList||| �̷��� ��ȯ�ǰ�,
new%0(��)�� �����ϴ� ��ũ�ΰ� �ٽ� �� �� �� ȣ�� ��.*/
#define QCONTAINER_CONTLOOP_2|||%0|||%1|||%2||| %1=QCONTAINER_CONTLOOP_4|||QCONTAINER_CONTLOOP_3|||%1:%2|||

/*'new ������'���� ������ �� new%0 ��ũ�ΰ� ����Ǹ� QCONTAINER_CONTLOOP_3|||i=QCONTAINER_CONTLOOP_4|||new i|||playerList�� ��ȯ�Ǹ�
QCONTAINER_CONTLOOP_5;i|||QCONTAINER_CONTLOOP_6|||playerList||| �̷��� ��ȯ�ǰ�,
QCONTAINER_CONTLOOP_5;%0�� �����ϴ� ��ũ�ΰ� ȣ���.*/
#define QCONTAINER_CONTLOOP_3|||%0=QCONTAINER_CONTLOOP_4|||%1|||%2||| new QCONTAINER_CONTLOOP_5;%0|||QCONTAINER_CONTLOOP_6|||%2|||

// new�� ���� ���������θ� ������ �� ȣ��Ǵ� ��ũ��
#define QCONTAINER_CONTLOOP_4|||QCONTAINER_CONTLOOP_3|||%0:%1||| CONTAINER_ARRAY_SIZE(%1); (%0 = _: %1[%0]) < CONTAINER_ARRAY_SIZE(%1);

// 'new ������'���� ������ �� ȣ��Ǵ� ��ũ��
#define QCONTAINER_CONTLOOP_5;%0|||QCONTAINER_CONTLOOP_6|||%1||| %0 = CONTAINER_ARRAY_SIZE(%1); (%0 = _: %1[%0]) < CONTAINER_ARRAY_SIZE(%1);

// 'new �±׸�: ������'���� ������ �� ȣ��Ǵ� ��ũ��
#define QCONTAINER_CONTLOOP_6|||%0QCONTAINER_CONTLOOP_5;%1|||%2|||%3||| new %1: %2 = %1: (CONTAINER_ARRAY_SIZE(%3)); _: (%2 = %1: %3[_: %2]) < CONTAINER_ARRAY_SIZE(%3);

/*�� ù��°�� ���� ���� �׻� �� ������ �迭�� ����, �ش� ������ �����ϴ� �ε������� �� ������ �迭�� �� �ִ� �迭 ũ�� - 1�� �� ������ �����Ŵ.
�� �Ŀ� ���� ���� ���� ��� ������ ���Դ� ���� 1�̾��� �״��� 2�� ���ٸ� 1�� �ε����� 2�� ���� 2�� �ε����� ���� 1�� �ε����� ������ �־��� ���� ��.
���� �ݴ�� ������ ���Դ� ���� 2�̾��� �״��� 1�� ���ٸ� 2�� �� �ִ� �ε����� 1�� ä��� 1�� �ε����� 2�� ��.

�迭���� �迭 ũ�� - 1���� ���� ���� �� �ִٸ� �� �������� ������ �迭�� ����Ŵ�� ���ÿ� ������ �� �ִ� ���� �Ǵ� ���̰�
�迭���� �迭 ũ�� - 1�� �� �ִٸ� �ش� �ε����� ������ ���̶�� ����.
�迭���� �迭 ũ�� - 1���� ū ���� �� �ִٸ� ���� �ش� �ε������� ������ ������ �ʾҴٴ� ����.*/
stock AddContainerData(QContainer: contArray[], inputValue, size = sizeof(contArray))
{
	--size;
	
	if (inputValue < 0 || inputValue >= size || _: contArray[inputValue] <= size) return 0;
	
	new currentIndex = size, nextValue = _: contArray[currentIndex];
	
	while (nextValue < inputValue)
	{
		currentIndex = nextValue;
		nextValue = _: contArray[currentIndex];
	}
	
	contArray[currentIndex] = QContainer: inputValue;
	contArray[inputValue] = QContainer: nextValue;
	
	return 1;
}

/*���� ���� �� ���� ���� ���¶�� ��ٷ� �ش� ������ �����ϴ� �ε����� �� �ִ� �迭 ũ�� - 1�� �� ������ �ε����� ����,
�ش� ������ �����ϴ� �ε������� �迭 ũ�� - 1���� ū ���� �־ Ȥ�ó� ���� ������ ������ ������.

���� ���� �������� ���� ���¶�� ������ ���� �� �ε����� ã�� ������ ������ �����ϴ� �ε����� �ִ� ���� �ְ�(��, �������� ������ �ε����� �������� �˸��� �迭 ũ�� - 1�� �� ����),
������ ������ �����ϴ� �ε������� �迭 ũ�� - 1���� ū ���� �־� �������� ������ ������ ���ܽ�Ŵ.*/
stock RemoveContainerData(QContainer: contArray[], rmvValue, size = sizeof(contArray))
{
	--size;
	
	if (rmvValue < 0 || rmvValue >= size || _: contArray[rmvValue] > size) return 0;
	
	new currentIndex = size, nextValue = _: contArray[currentIndex];
	
	while (nextValue != rmvValue)
	{
		currentIndex = nextValue;
		nextValue = _: contArray[currentIndex];
	}
	
	contArray[currentIndex] = contArray[rmvValue];
	contArray[rmvValue] = QContainer: (size + 1);
	
	return 1;
}