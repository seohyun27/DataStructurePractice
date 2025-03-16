#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))
#define COMPARE(x,y) ( ((x)<(y)) ? -1 : ((x)==(y)) ? 0 : 1 )
// ( if : else if : else )

void sort(int list[], int n);
int is_sorted(int A[], int n);
int binsearch(int list[], int searchnum, int left, int right);

int counter

void main(void)
{
	//int n = 100000; 선언해두고 숫자 대신에 n으로 사용
	int A[100000];
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 100000; i++) {
		A[i] = rand() % 100000 + 1;
	}

	sort(A, 100000);
	if (is_sorted(A, 100000) == 0)
		printf("정렬이 완료되지 않았습니다.");
	else
		printf("정렬이 완료되었습니다.\n\n");

	int targetnum;

	 while (1) {
		printf("검색 데이터 (1~100000) : ");
		scanf_s("%d", &targetnum);
		//targetnum에 대한 처리 필요(검색 범위를 벗어날 경우 경고 문구를 띄우도록)

		if (targetnum == -1){
			printf("프로그램이 종료되었습니다.");
			break;
		}

		printf("검색 데이터 : %d\n", targetnum);
		binsearch(A, targetnum, 0, 99999);
		printf("count = %d\n", counter);
	 }

}

int binsearch(int list[], int searchnum, int left, int right) //이진 검색 알고리즘
{
	counter = 0;
	int middle;
	while (left <= right) {
		middle = (left + right) / 2;
		switch (COMPARE(list[middle],searchnum))
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