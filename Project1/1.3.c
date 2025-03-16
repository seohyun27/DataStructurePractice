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
	//int A[200000]; //정적으로 배열을 할당했을 때 배열의 수가 300000이 되면 작동하지 않았음
	int* A;
	double duration;
	clock_t start;

	printf("n\t 시간\t\t 정렬상태\n");
	for (n = 0; n <= 1000000; n += step) {
		A = (int*)malloc(n * sizeof(int)); //동적으로 메모리 할당
		for (i = 0;i < n;i++)
			A[i] = n - i;

		start = clock();
		sort(A, n);
		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC; //sort 시간측정

		printf("%6d\t %f\t", n, duration); //만든 시간을 출력
		if (is_sorted(A, n) == 0)
			printf("정렬 오류\n");
		else
			printf("정렬 완료\n");

		free(A); //할당했던 메모리를 해제

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