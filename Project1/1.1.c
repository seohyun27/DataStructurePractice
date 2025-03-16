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
	//뒤에서 -50000을 한 다음에 한 번 더 돌아가도록 작성했었어야 함!!
	//조건에서 나온 걸 코드에서 다 드러낼 수 있도록 할 것!
	//아니면 주석 처리라도 하던가!
	int A[100000];
	for (int i = 0;i < n;i++)
		A[i] = n - i;

	sort(A, n);
	if (is_sorted(A, n) == 0)
		printf("정렬이 완료되지 않았습니다.");
	else
		printf("정렬이 완료되었습니다.\n\n");

	int targetnum;

	while (1) {
		printf("검색 데이터 (1~%d) : ", n);
		scanf_s("%d", &targetnum);

		if (targetnum == -1) {
			printf("프로그램이 종료되었습니다.\n");
			break;
		}

		printf("검색 데이터 : %d\n", targetnum);
		binsearch(A, targetnum, 0, n-1);
		printf("count = %d\n", counter);
	}

}

int binsearch(int list[], int searchnum, int left, int right) //이진 검색 알고리즘
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
	return -1; //찾고자 하는 숫자가 배열 안에 존재하지 않음
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