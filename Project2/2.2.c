#include <stdio.h>
#include <time.h>

#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))
//�ƽ� ����� ���⼭ �����ؼ� ����ó�� ����� ���� ����

void perm(int* list, int i, int n);

void main(void)
{
	int num;
	double duration;
	clock_t start;

	printf("2.2. 1���� n������ ���ڵ��� �̿��� ����\n");
	while (1)
	{
		printf("�Է� : ");
		scanf_s("%d", &num);

		if (num < 0)
		{
			printf("����\n");
			break;
		}
		if (num < 1 || num > 32)
		{
			printf("�Է� ����(1~32)�� ������ϴ�.\n");
			continue;
		}

		int list[32];
		for (int i = 0; i < num; i++)
		{
			list[i] = i + 1;
		}

		printf("���� :\n");
		start = clock(); //���� �� �ð��� ���
		perm(list, 0, num-1);
		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC; //���� �� �ð� - ���� �� �ð�
		printf("\n����ð� : %.3f\n", duration);
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
			perm(list, i + 1, n); //����Լ�
			SWAP(list[i], list[j], temp);
		}
	}
}