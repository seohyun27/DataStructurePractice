#include <stdio.h>
#include <string.h> //strlen()이 포함된 헤더 파일 -> 지우고 배열 개수 세는 알고리즘 만들어서 사용하기
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

void perm(char* list, int i, int n);

void main(void)
{
	printf("2.1.순열 알고리즘 호출\n");
	char A[4][6] = { "GO", "BOY", "GIRL", "GIRLS" };
	for (int i = 0; i < 4; i++)
	{
		printf("제시 문자열 : ");
		puts(A[i]);
		perm(A[i], 0, strlen(A[i])-1);
		printf("\n");
	}
}

void perm(char* list, int i, int n)
{
	int j, temp;
	if (i == n) {
		for (j = 0; j <= n;j++)
			printf("%c", list[j]);
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