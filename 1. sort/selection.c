#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t)) //��ũ�� ����

void sort(int list[], int n);
int is_sorted(int A[], int n);

void main(void)
{
	int A[100000];
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 100000; i++) { //100,000���� ���� ����
		A[i] = rand() % 100000 + 1;
	}
	printf("�迭 A�� 100,000���� ������ �������� �����Ͽ� ����\n");
	for (int i = 0; i < 100; i++)
	{
		printf("%d\t", A[i]);
	}
	printf(".....");
	printf("\n\n");

	sort(A, 100000); //����Ʈ A�� �״�� �Ѱܾ� ��
	printf("�迭 A�� �������� ����� ������ ����\n");
	for (int i = 0; i < 100; i++)
	{
		printf("%d\t", A[i]);
	}
	printf(".....");
	printf("\n\n");

	printf("�迭 A�� ���ĵ� ������ ���� ���� Ȯ��\n");
	if (is_sorted(A, 100000) == 0)
		printf("������ �Ϸ���� �ʾҽ��ϴ�.");
	else
		printf("������ �Ϸ�Ǿ����ϴ�.\n\n");

}

void sort(int list[], int n)
{
	int i, j, min, temp;
	for (i = 0; i < n - 1;i++) {
		min = i;
		for (j = i + 1;j < n;j++)
			if (list[j] < list[min])
				min = j;
		SWAP(list[i], list[min], temp);
	}
}

int is_sorted(int A[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		if (A[i] > A[i + 1]) return 0;
	}
	return 1;
}