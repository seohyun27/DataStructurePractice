#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))
#define N_START 1000
#define N_MAX 1000000

void sort(int list[], int n); //선택 정렬
int is_sorted(int A[], int n); //확인 함수
void arrayCopy(int A[], int B[], int n, int start_n);
void insert(int e, int a[], int i);
void insertionSort(int a[], int n); //삽입 정렬
void quickSort(int a[], int left, int right); //빠른 정렬

void main(void)
{
	int n;
	int* A;
	int* B;
	double duration;
	clock_t start;

	printf("12.2. 정렬된 데이터의 정렬\n");
	printf("12.2.1. 오름차순 정렬된 데이터의 정렬\n");
	for (n = N_START; n <= N_MAX; n *= 10) {
		A = (int*)malloc((n + 2) * sizeof(int)); //A,B 배열 동적 할당
		B = (int*)malloc((n + 2) * sizeof(int));

		for (int i = 0; i < n; i++)
		{
			A[i] = i;
		}

		printf("  원소 수 : %d\n", n);
		
		arrayCopy(A, B, n, 0); //A배열을 B배열에 복사
		start = clock();
		sort(B, n); //원본 대신 복사본인 B 리스트를 정렬해야 함
		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		printf("  selection sort time : %f\n", duration); //만든 시간을 출력
		if (is_sorted(B, n) == 0)
			printf("정렬이 완료되지 않았습니다.\n");

		free(B);
		B = (int*)malloc((n + 2) * sizeof(int));
		arrayCopy(A, B, n, 1);
		start = clock();
		insertionSort(B, n + 1);
		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		printf("  insertion sort time : %f\n", duration); //만든 시간을 출력
		if (is_sorted(B, n) == 0)
			printf("정렬이 완료되지 않았습니다.\n");

		free(B);
		B = (int*)malloc((n + 2) * sizeof(int));
		arrayCopy(A, B, n, 1);
		start = clock();
		quickSort(B, 0, n-1);
		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		printf("      quick sort time : %f\n", duration); //만든 시간을 출력
		if (is_sorted(B, n) == 0)
			printf("정렬이 완료되지 않았습니다.\n");

		printf("\n");
		free(A); //할당했던 메모리를 해제
		free(B);
	}

	printf("12.2.2. 내림차순 정렬된 데이터의 정렬\n");
	for (n = N_START; n <= N_MAX; n *= 10) {
		A = (int*)malloc((n + 2) * sizeof(int)); //A,B 배열 동적 할당
		B = (int*)malloc((n + 2) * sizeof(int));

		for (int i = 0; i < n; i++)
		{
			A[i] = n - i;
		}

		printf("  원소 수 : %d\n", n);

		arrayCopy(A, B, n, 0); //A배열을 B배열에 복사
		start = clock();
		sort(B, n); //원본 대신 복사본인 B 리스트를 정렬해야 함
		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		printf("  selection sort time : %f\n", duration); //만든 시간을 출력
		if (is_sorted(B, n) == 0)
			printf("정렬이 완료되지 않았습니다.\n");

		free(B);
		B = (int*)malloc((n + 2) * sizeof(int));
		arrayCopy(A, B, n, 1);
		start = clock();
		insertionSort(B, n + 1);
		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		printf("  insertion sort time : %f\n", duration); //만든 시간을 출력
		if (is_sorted(B, n) == 0)
			printf("정렬이 완료되지 않았습니다.\n");

		free(B);
		B = (int*)malloc((n + 2) * sizeof(int));
		arrayCopy(A, B, n, 1);
		start = clock();
		quickSort(B, 0, n-1);
		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		printf("      quick sort time : %f\n", duration); //만든 시간을 출력
		if (is_sorted(B, n) == 0)
			printf("정렬이 완료되지 않았습니다.\n");

		printf("\n");
		free(A); //할당했던 메모리를 해제
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
	for (i = start_n; i < n + start_n;i++)
	{
		B[i] = A[i - start_n];

	}
}

void insert(int e, int a[], int i)
{
	a[0] = e; //삽입하려는 숫자를 a[0]에 임시로 저장
	while (e < a[i]) //삽입하려는 숫자가 a[i]보다 작다면
	{
		a[i + 1] = a[i]; //현재 요소를 한 칸 뒤로 이동
		i--;
	}
	a[i + 1] = e; //잡은 위치에다 삽입
}

void insertionSort(int a[], int n)
{
	int j;
	for (j = 1;j <= n;j++) //1번 자리는 insert함수에서 항상 사용하므로 비워둬야 함
	{
		int temp = a[j];
		insert(temp, a, j - 1);
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
		pivot = a[left]; //기준
		do
		{
			do i++; while (i <= right && a[i] < pivot); //기준보다 작은 수는 왼쪽으로
			do j--; while (j >= left && a[j] > pivot);
			if (i < j)
				SWAP(a[i], a[j], temp);
		} while (i < j);
		SWAP(a[left], a[j], temp);
		quickSort(a, left, j - 1);
		//if 조건을 불만족할 때까지 pivot를 기준으로 나뉜 영역에 재귀함수로 quickSort를 각각 사용
		quickSort(a, j + 1, right);
	}
}