#include <stdio.h>
#include <time.h>

#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))
//맥스 사이즈를 여기서 지정해서 숫자처럼 사용할 수도 있음

void perm(int* list, int i, int n);

void main(void)
{
	int num;
	double duration;
	clock_t start;

	printf("2.2. 1부터 n사이의 숫자들을 이용한 순열\n");
	while (1)
	{
		printf("입력 : ");
		scanf_s("%d", &num);

		if (num < 0)
		{
			printf("종료\n");
			break;
		}
		if (num < 1 || num > 32)
		{
			printf("입력 범위(1~32)를 벗어났습니다.\n");
			continue;
		}

		int list[32];
		for (int i = 0; i < num; i++)
		{
			list[i] = i + 1;
		}

		printf("순열 :\n");
		start = clock(); //실행 전 시간을 기록
		perm(list, 0, num-1);
		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC; //정렬 후 시간 - 정렬 전 시간
		printf("\n실행시간 : %.3f\n", duration);
	}
}


void perm(int* list, int i, int n)
{
	int j, temp;
	if (i == n) {
		for (j = 0; j <= n;j++)
			printf("%d", list[j]);
		printf("\t");
	}
	else {
		for (j = i; j <= n;j++) {
			SWAP(list[i], list[j], temp);
			perm(list, i + 1, n); //재귀함수
			SWAP(list[i], list[j], temp);
		}
	}
}