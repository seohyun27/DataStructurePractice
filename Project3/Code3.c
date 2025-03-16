#define _CRT_SECURE_NO_WARNINGS //scanf, strcpy���� _s�� ������ �ʾƵ� ������ ���� �ʵ��� ���ִ� �ڵ�
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#define COMPARE(x,y) ( ((x)<(y)) ? -1 : ((x)==(y)) ? 0 : 1 )
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
#define MAX_TERMS 10

//struct �ڿ� ����ü�� �̸��� �� �� �� ������ִ� ���� ����
//struct �ڿ� polynomial�� ����ϸ� struct polynomial�� ����� �� �ִ�
//����ϴ� ���� ��õ
typedef struct polynomial {
	float coef; //���
	int expon; //����
}polynomial;

//polynomial ��� struct polynomial�� ����ϸ� ���� �߻��� ���� �� ����
struct polynomial* A, * B, * D;

//��� ���׽Ŀ� ���� �� ��ġ�� D ����� ǥ���ϴ� ������ �ϳ��� �ʿ���
int k; //���� �� ��ġ
int max_D; //D ������

void print(polynomial* A)
{
	printf("    coef   expon\n");
	for (int n = 0;A[n].expon >= 0;n++)
		printf("%8.2f %8d\n", A[n].coef, A[n].expon);
}

void attach(float coef, int expon)
{
	//����ġ ���� �迭�� �ڸ��� �����ִ��� Ȯ��
	if(k==max_D) //���� ��ġ�� D�� ����� ���ٸ�(�ڸ�X)
	{
		//D�� ����� Ű���� ���Ҵ�
		max_D += MAX_TERMS;
		D = (polynomial*)realloc(D, sizeof(struct polynomial) * max_D);
		//���Ҵ� �ÿ��� �Ҵ� ���п� ���� �ڵ带 �־��ִ� ���� �����
	}

	D[k].coef = coef;
	D[k].expon = expon;
	k++;
}

polynomial* padd(polynomial* A, polynomial* B)
//2���� polynomial�迭�� �Է¹޾� ��� polynomial �迭�� ��ȯ�ϴ� �Լ�
{
	float coef;
	int i = 0, j = 0;
	while (A[i].expon >= 0 && B[j].expon >= 0) //���׽� A, B�߿� �ϳ��� ���� ���� ������
	{
		switch (COMPARE(A[i].expon, B[j].expon)) //�� ���� ���� ��
		{
		case -1: //B ������ Ŭ ��
			attach(B[j].coef, B[j].expon); //B���� �״�� ����ġ
			j++;
			break;
		case 0:
			coef = A[i].coef + B[j].coef; //A B ��� ���ϱ�
			if (coef) //����� 0�� �ƴ϶��
				attach(coef, A[i].expon);
			i++;
			j++;
			break;
		case 1:
			attach(A[i].coef, A[i].expon); //A���� �״�� ����ġ
			i++;
		}
	}
	//���׽� A, B�߿� �ϳ��� ���� ������ ��
	//���� ���׽��� ���� ��� ����ġ ����
	for (; A[i].expon >= 0; i++) //A�� ������ ��
		attach(A[i].coef, A[i].expon);
	for (; B[j].expon >= 0; j++)//B�� ������ ��
		attach(B[j].coef, B[j].expon);

	attach(-1, -1); //D �迭�� ������
	return D; //�迭 D ��ȯ
}

polynomial* single_mul(polynomial Ai, polynomial* B)
//A���׽��� �� �ϳ��� B���׽��� ���ϴ� �Լ�
{
	int max_Cj = MAX_TERMS; //Cj ������
	int i = 0; //Cj ���� ��ġ

	//����� ������ �迭
	polynomial* Cj = (polynomial*)malloc(sizeof(struct polynomial) * max_Cj);
	for (int j = 0; B[j].expon >= 0; j++)
	{
		if (i == max_Cj) { //Cj ���� ��ġ�� Cj �迭�� ������ �����ߴٸ�
			max_Cj += MAX_TERMS;
			Cj = (polynomial*)realloc(Cj, sizeof(struct polynomial) * max_Cj);
		}
		Cj[i].coef = Ai.coef * B[j].coef;
		Cj[i].expon = Ai.expon + B[j].expon;
		i++;
	}
	Cj[i].coef = -1;
	Cj[i].expon = -1; //��谪 ǥ��

	return Cj;
}

polynomial* pmul(polynomial* A, polynomial* B)
//�� ���׽��� ���� ���ϴ� �Լ�
{
	polynomial* Cj; //single_mul(Ai, B)�� ����� �����ϴ� �迭
	polynomial* Ci; //Cj�� ���� �������� �迭

	int max_Ci = MAX_TERMS; //Ci ������
	int h = 0; //Ci ���� ��ġ

	Ci = (polynomial*)malloc(sizeof(struct polynomial) * max_Ci);
	Ci[0].coef = -1;
	Ci[0].expon = -1;

	for (int i = 0; A[i].expon >= 0; i++) //A�� ������ ������ �ɶ�����
	{
		//�̰��� Cj�� single_mul(Ai, B)���� ���ϵ� Cj �迭�� �״�� �Ѱܹ���
		//���� �迭�� ũ�⸦ ������� �� �ʿ䰡 ���� ��
		Cj = single_mul(A[i], B);
		printf("singul_mul - C%d\n", i + 1);
		print(Cj); //�߰� ��� ���
		D = padd(Ci, Cj);
		free(Cj);
		free(Ci);

		if(A[i+1].expon >= 0) //���� A�� ���� ���� �����Ѵٸ�
		{
			Ci = D; //�迭 B�� Ci�ȿ� ��Ƶα�
			//D �迭, D���� ��ġ �ʱ�ȭ
			D = (polynomial*)malloc(sizeof(struct polynomial) * max_D);
			k = 0;
		}
	}
	return D;
}

void sortpoly(polynomial* A)
//���׽� ���� �Լ�
//������ �������� ���, ������ ����
{
	int i, j, max;
	int temp; //���� �ӽ� ���� ���
	float tempf; //��� �ӽ� ���� ���

	for (i = 0;A[i].expon > -1;i++)
	{
		max = i;
		for (j = i + 1; A[j].expon > -1; j++)
			if (A[j].expon > A[max].expon)
				max = j;
		SWAP(A[i].expon, A[max].expon, temp);
		SWAP(A[i].coef, A[max].coef, tempf);
	}
}


int main()
{
	float coef;
	int expon;
	int n = 0, max_A;
	int m = 0, max_B;
	
	while (1)
	{
		max_A = max_B = MAX_TERMS;

		A = (polynomial*)malloc(sizeof(struct polynomial) * max_A);
		B = (polynomial*)malloc(sizeof(struct polynomial) * max_B);

		printf("3.1. ���׽� ����\n");
		// A���׽� ����
		while (1)
		{
			printf("A(x)�� ���� �Է��ϼ���. (coef expon) : ");
			scanf_s("%f %d", &coef, &expon);
			A[n].coef = coef;
			A[n].expon = expon;
			n++;

			if (expon < 0)
				break;

			//�迭�� �ڸ��� ���Ҵ��� Ȯ��
			if (n == max_A - 1) {
				max_A += MAX_TERMS;
				A = (polynomial*)realloc(A, sizeof(struct polynomial) * max_A);
			}
		}
		sortpoly(A); //�迭 A�� ���� �������� ����
		printf("���׽� A(x)\n");
		print(A); //�迭 ��� �Լ�


		// B���׽� ����
		while (1)
		{
			printf("B(x)�� ���� �Է��ϼ���. (coef expon) : ");
			scanf_s("%f %d", &coef, &expon);
			B[m].coef = coef;
			B[m].expon = expon;
			m++;

			if (expon < 0)
				break;

			if (m == max_B - 1)
			{
				max_B += MAX_TERMS;
				B = (polynomial*)realloc(B, sizeof(struct polynomial) * max_B);
			}
		}
		sortpoly(B);
		printf("���׽� B(x)\n");
		print(B);


		printf("3.2 ���׽� ����\n");
		//�迭 D�Ҵ�
		max_D = MAX_TERMS;
		k = 0; //D�� ���� ��ġ �ʱ�ȭ
		D = (polynomial*)malloc(sizeof(struct polynomial) * max_D);
		D = padd(A, B); //���׽� ���� �Լ� ����
		printf("���׽� ���� ��� : D(x)\n");
		print(D);
		free(D);


		printf("3.3 ���׽� ����\n");
		//�迭 D�Ҵ�
		max_D = MAX_TERMS;
		k = 0;
		D = (polynomial*)malloc(sizeof(struct polynomial) * max_D);
		D = pmul(A, B); //���׽� ���� �Լ� ����
		printf("���׽� ���� ��� : D(x)\n");
		print(D);
	}
	return 0;
}