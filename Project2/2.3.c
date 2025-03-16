#include <stdio.h>
#include <time.h>

#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

void perm(int* list, int i, int n);

void main(void)
{
	int n = 1;
	double duration[10];
	clock_t start;

	printf("2.3. ���� ���� ������ ��ȭ��Ű�鼭 ���� �ð� ����\n");
	while (n < 10)
	{
		int list[10];
		for (int i = 0; i < n; i++)
		{
			list[i] = i + 1;
		}
		start = clock(); //���� �� �ð��� ���
		perm(list, 0, n - 1);
		duration[n-1] = ((double)(clock() - start)) / CLOCKS_PER_SEC; //���� �� �ð� - ���� �� �ð�
		printf("\n");
		n++;
	}
	printf("\n���Ұ���\t����ð�\n");
	for (int i = 1; i < n; i++) {
		printf("  %d\t\t%.3f\n", i, duration[i-1]);
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