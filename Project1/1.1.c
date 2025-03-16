#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))
#define COMPARE(x,y) ( ((x)<(y)) ? -1 : ((x)==(y)) ? 0 : 1 )

void sort(int list[], int n);
int is_sorted(int A[], int n);
int binsearch(int list[], int searchnum, int left, int right);

int counter;

void main(void)
{
	int n = 100000;
	//�ڿ��� -50000�� �� ������ �� �� �� ���ư����� �ۼ��߾���� ��!!
	//���ǿ��� ���� �� �ڵ忡�� �� �巯�� �� �ֵ��� �� ��!
	//�ƴϸ� �ּ� ó���� �ϴ���!
	int A[100000];
	for (int i = 0;i < n;i++)
		A[i] = n - i;

	sort(A, n);
	if (is_sorted(A, n) == 0)
		printf("������ �Ϸ���� �ʾҽ��ϴ�.");
	else
		printf("������ �Ϸ�Ǿ����ϴ�.\n\n");

	int targetnum;

	while (1) {
		printf("�˻� ������ (1~%d) : ", n);
		scanf_s("%d", &targetnum);

		if (targetnum == -1) {
			printf("���α׷��� ����Ǿ����ϴ�.\n");
			break;
		}

		printf("�˻� ������ : %d\n", targetnum);
		binsearch(A, targetnum, 0, n-1);
		printf("count = %d\n", counter);
	}

}

int binsearch(int list[], int searchnum, int left, int right) //���� �˻� �˰���
{
	counter = 0;
	int middle;
	while (left <= right) {
		middle = (left + right) / 2;
		switch (COMPARE(list[middle], searchnum))
		{
		case -1: //list[middle] < searchnum
			left = middle + 1;
			break;
		case 0:
			return middle;
		case 1:
			right = middle - 1;
		}
		counter += 1;
	}
	counter = -1;
	return -1; //ã���� �ϴ� ���ڰ� �迭 �ȿ� �������� ����
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