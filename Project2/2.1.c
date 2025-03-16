#include <stdio.h>
#include <string.h> //strlen()�� ���Ե� ��� ���� -> ����� �迭 ���� ���� �˰��� ���� ����ϱ�
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

void perm(char* list, int i, int n);

void main(void)
{
	printf("2.1.���� �˰��� ȣ��\n");
	char A[4][6] = { "GO", "BOY", "GIRL", "GIRLS" };
	for (int i = 0; i < 4; i++)
	{
		printf("���� ���ڿ� : ");
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
			perm(list, i + 1, n); //����Լ�
			SWAP(list[i], list[j], temp);
		}
	}
}