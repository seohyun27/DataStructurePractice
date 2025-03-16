#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t)) //매크로 구현

void sort(int list[], int n);
int is_sorted(int A[], int n);

void main(void)
{
	int A[100000];
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 100000; i++) { //100,000개의 난수 생성
		A[i] = rand() % 100000 + 1;
	}
	printf("배열 A에 100,000개의 정수를 무작위로 생성하여 저장\n");
	for (int i = 0; i < 100; i++)
	{
		printf("%d\t", A[i]);
	}
	printf(".....");
	printf("\n\n");

	sort(A, 100000); //리스트 A를 그대로 넘겨야 함
	printf("배열 A에 무작위로 저장된 정수를 정렬\n");
	for (int i = 0; i < 100; i++)
	{
		printf("%d\t", A[i]);
	}
	printf(".....");
	printf("\n\n");

	printf("배열 A에 정렬된 정수의 정렬 상태 확인\n");
	if (is_sorted(A, 100000) == 0)
		printf("정렬이 완료되지 않았습니다.");
	else
		printf("정렬이 완료되었습니다.\n\n");

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