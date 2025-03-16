#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

void sort(int list[], int n);
int is_sorted(int A[], int n);


void main(void)
{
	int i, n, step = 10;
	int n_max = 100;
	//int A[200000]; //�������� �迭�� �Ҵ����� �� �迭�� ���� 300000�� �Ǹ� �۵����� �ʾ���
	int* A;
	double duration;
	clock_t start;

	printf("n\t �ð�\t\t ���Ļ���\n");
	for (n = 0; n <= 1000000; n += step) {
		A = (int*)malloc(n * sizeof(int)); //�������� �޸� �Ҵ�
		for (i = 0;i < n;i++)
			A[i] = n - i;

		start = clock();
		sort(A, n);
		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC; //sort �ð�����

		printf("%6d\t %f\t", n, duration); //���� �ð��� ���
		if (is_sorted(A, n) == 0)
			printf("���� ����\n");
		else
			printf("���� �Ϸ�\n");

		free(A); //�Ҵ��ߴ� �޸𸮸� ����

		if (n == n_max) {
			step *= 10;
			n_max *= 10;
		}
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