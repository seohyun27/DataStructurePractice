#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

void sort(int list[], int n); //���� ���� -> �̸��� selectionSort�� �ٲ�� �ҵ�
int is_sorted(int A[], int n); //Ȯ�� �Լ�
void arrayCopy(int A[], int B[], int n, int start_n);
void insert(int e, int a[], int i);
void insertionSort(int a[], int n); //���� ����
void quickSort(int a[], int left, int right); //���� ����

void main(void)
{
	int n;
	int* A;
	int* B;
	double duration;
	clock_t start;

	printf("12.1. ���� ���� �������� ����\n");
	for (n = 1000; n <= 1000000; n *= 10) {
		A = (int*)malloc((n + 2) * sizeof(int)); //A,B �迭 ���� �Ҵ�
		B = (int*)malloc((n + 2) * sizeof(int));

		srand((unsigned int)time(NULL));
		for (int i = 0; i < n; i++)
		{
			A[i] = (rand() / (0x7fff * 1.0)) * n; //���� ����
		}

		/*
		//����Ʈ Ȯ�ο� �ڵ�
		for (int i = 0; i < 100; i++)
		{
			printf("%d %d\t", i, B[i]);
		}
		printf("\n\n");
		*/

		printf("  ���� �� : %d\n", n);

		arrayCopy(A, B, n, 0); //A�迭�� B�迭�� ����
		start = clock();
		sort(B, n); //���� ��� ���纻�� B ����Ʈ�� �����ؾ� ��
		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		printf("  selection sort time : %f\n", duration); //���� �ð��� ���
		if (is_sorted(B, n) == 0)
			printf("������ �Ϸ���� �ʾҽ��ϴ�.\n");

		free(B);
		B = (int*)malloc((n + 2) * sizeof(int));
		arrayCopy(A, B, n, 1);
		start = clock();
		insertionSort(B, n+1);
		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		printf("  insertion sort time : %f\n", duration); //���� �ð��� ���
		if (is_sorted(B, n) == 0)
			printf("������ �Ϸ���� �ʾҽ��ϴ�.\n");

		free(B);
		B = (int*)malloc((n + 2) * sizeof(int));
		arrayCopy(A, B, n, 0);
		start = clock();
		quickSort(B, 0, n - 1);
		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		printf("      quick sort time : %f\n", duration); //���� �ð��� ���
		if (is_sorted(B, n) == 0)
			printf("������ �Ϸ���� �ʾҽ��ϴ�.\n");

		printf("\n");
		free(A); //�Ҵ��ߴ� �޸𸮸� ����
		free(B);
	}
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

void arrayCopy(int A[], int B[], int n, int start_n)
{
	int i;
	for (i = start_n; i < n + start_n; i++)
	{
		B[i] = A[i - start_n];

	}
}

void insert(int e, int a[], int i)
{
	a[0] = e; //�����Ϸ��� ���ڸ� a[0]�� �ӽ÷� ����
	while (e < a[i]) //�����Ϸ��� ���ڰ� a[i]���� �۴ٸ�
	{
		a[i + 1] = a[i]; //���� ��Ҹ� �� ĭ �ڷ� �̵�
		i--;
	}
	a[i + 1] = e; //���� ��ġ���� ����
}

void insertionSort(int a[], int n)
{
	int j;
	for (j = 1;j <= n;j++) //1�� �ڸ��� insert�Լ����� �׻� ����ϹǷ� ����־� ��
	{
		int temp = a[j];
		insert(temp, a, j-1);
	}
}

void quickSort(int a[], int left, int right)
{
	int pivot, i, j;
	int temp;
	if (left < right)
	{
		i = left;
		j = right + 1;
		pivot = a[left]; //����
		do
		{
			do i++; while (a[i] < pivot); //���غ��� ���� ���� ��������
			do j--; while (a[j] > pivot);
			if (i < j)
				SWAP(a[i], a[j], temp);
		} while (i < j);
		SWAP(a[left], a[j], temp);
		quickSort(a, left, j - 1);
		//if ������ �Ҹ����� ������ pivot�� �������� ���� ������ ����Լ��� quickSort�� ���� ���
		quickSort(a, j + 1, right);
	}
}