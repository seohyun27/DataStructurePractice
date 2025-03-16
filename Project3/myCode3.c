#include <stdio.h>
#include <stdlib.h>

#define COMPARE(x,y) ( ((x)<(y)) ? -1 : ((x)==(y)) ? 0 : 1 )

typedef struct polynomial { //���׽� ����ü
	float coef; //���
	int expon; //����
}polynomial;
//struct �ڿ� polynomial�� ����ϸ� struct polynomial�� �θ� �� ��
//����ϴ� ���� ��õ

//��� ���׽Ŀ� ���� �� ��ġ�� D ����� ǥ���ϴ� ������ �ϳ��� �ʿ���
int k; //���� �� ��ġ
int max_D; //D ������

polynomial* A;
polynomial* B;
polynomial* D;
polynomial* Ci;
int size; //�迭�� ũ��
int count; //�ε��� ��
int Ci_size;
int Ci_count;
int old_count;

void attach(float coef, int expon, polynomial* D);
polynomial* padd(polynomial* A, polynomial* B, polynomial* D);
polynomial* single_mul(polynomial Ai, polynomial* B, polynomial* Ci);
polynomial* pmul(polynomial* A, polynomial* B, polynomial* D);

void main(void)
{
	while (1)
	{
		A = (polynomial*)malloc(sizeof(polynomial) * 10); //�ʱ� �Ҵ�
		B = (polynomial*)malloc(sizeof(polynomial) * 10);
		D = (polynomial*)malloc(sizeof(polynomial) * 10);

		size = 10;
		count = 0;
		Ci_size = 10;
		Ci_count = 0;

		int A_size = 10;
		int A_count = 0;
		int B_size = 10;
		int B_count = 0;

		printf("3.1. ���׽� ����\n");
		// ���׽� A(x) �Է�
		while (1)
		{
			float coef;
			int expon;

			printf("A(x)�� ���� �Է��ϼ���. (coef expon) : ");
			scanf_s("%f %d", &coef, &expon);
			if (A_count >= A_size - 1) { //�迭�� �ڸ��� ���Ҵ��� Ȯ��
				A_size += 10;
				A = (polynomial*)realloc(A, A_size * sizeof(polynomial));
			}
			A[A_count].coef = coef;
			A[A_count].expon = expon;
			A_count++;

			if (expon == -1) {
				break;
			}
		}
		printf("\n");

		//���׽� A(x) ���
		printf("���׽� A(x)\n");
		printf("    coef      expon\n");
		for (int i = 0; i < A_count - 1; i++) { //-1�� ��� ������ ���� �����ϰ� ���
			printf("    %.2f\t%d\n", A[i].coef, A[i].expon);
		}
		printf("\n");

		// ���׽� B(x) �Է�
		while (1)
		{
			float coef;
			int expon;

			printf("B(x)�� ���� �Է��ϼ���. (coef expon) : ");
			scanf_s("%f %d", &coef, &expon);
			if (B_count >= B_size - 1) {
				B_size += 10;
				B = (polynomial*)realloc(B, B_size * sizeof(polynomial));
			}
			B[B_count].coef = coef;
			B[B_count].expon = expon;
			B_count++;

			if (expon == -1) {
				break;
			}
		}
		printf("\n");

		//���׽� B(x) ���
		printf("���׽� B(x)\n");
		printf("    coef      expon\n");
		for (int i = 0; i < B_count - 1; i++) {
			printf("    %.2f\t%d\n", B[i].coef, B[i].expon);
		}
		printf("\n");

		// ���׽��� ���� ��� ���
		printf("3.2 ���׽� ����\n");
		D = padd(A, B, D);
		printf("���׽� ���� ��� : D(x)\n");
		printf("    coef      expon\n");
		for (int i = 0; i < count; i++) {
			printf("    %.2f\t%d\n", D[i].coef, D[i].expon);
		}
		printf("\n");
		free(D);

		// ���׽��� ���� ��� ���
		count = 0;
		size = 10;
		D = (polynomial*)malloc(sizeof(polynomial) * 10);
		printf("3.3 ���׽� ����\n");
		D = pmul(A, B, D);

		free(A);
		free(B);
		free(D);
	}
}


void attach(float coef, int expon, polynomial* D)
{
	if (count >= size - 1) { //�迭�� �ڸ��� ���Ҵ��� Ȯ��
		size += 10;
		D = (polynomial*)realloc(D, size * sizeof(polynomial));
	}
	D[count].coef = coef;
	D[count].expon = expon;
	count++;
}

polynomial* padd(polynomial* A, polynomial* B, polynomial* D)
{
	int i = 0;
	int j = 0;
	float coef; //D���� attach�� ���� ����� �־�δ� ����

	while (A[i].expon != -1 && B[j].expon != -1) //���׽� A, B�߿� �ϳ��� ���� ���� ������
	{
		switch (COMPARE(A[i].expon, B[j].expon)) //�� ���� ���� ��
		{
		case -1: //B ������ Ŭ ��
			attach(B[j].coef, B[j].expon, D); //B���� �״�� ����ġ
			j++;
			break;
		case 0:
			coef = A[i].coef + B[j].coef; //A B ��� ���ϱ�
			if (coef) //����� 0�� �ƴ϶��
				attach(coef, A[i].expon, D);
			i++;
			j++;
			break;
		case 1:
			attach(A[i].coef, A[i].expon, D); //A���� �״�� ����ġ
			i++;
		}
	}
	//���׽� A, B�߿� �ϳ��� ���� ������ ��
	//���� ���׽��� ���� ��� ����ġ ����
	for (; A[i].expon != -1; i++) //A�� ������ ��
		attach(A[i].coef, A[i].expon, D);
	for (; B[j].expon != -1; j++)//B�� ������ ��
		attach(B[j].coef, B[j].expon, D);

	return D; //�迭 D ��ȯ
}

polynomial* single_mul(polynomial Ai, polynomial* B, polynomial* Ci)
//A�� �� �ϳ�(Ai)�� B�� ���׽��� ���ϴ� �Լ�
{
	Ci_count = 0;
	Ci_size = 10;

	for (int i = 0; B[i].expon != -1; i++)
	{
		if (Ci_count >= Ci_size - 1) { //Ci �迭�� �ڸ��� ���Ҵ��� Ȯ��
			Ci_size += 10;
			Ci = (polynomial*)realloc(Ci, Ci_size * sizeof(polynomial));
		}
		Ci[Ci_count].coef = Ai.coef * B[i].coef;
		Ci[Ci_count].expon = Ai.expon + B[i].expon;
		Ci_count++;
	}
	Ci[Ci_count].coef = -1;
	Ci[Ci_count].expon = -1;

	return Ci;
}

polynomial* pmul(polynomial* A, polynomial* B, polynomial* D)
{
	polynomial* temp = (polynomial*)malloc(sizeof(polynomial) * size); //temp �迭 ����

	//ù ��° ���� ����
	temp = single_mul(A[0], B, temp);
	count = 0;  // count �ʱ�ȭ

	//temp�� ����� D�� ����
	for (int i = 0; temp[i].expon != -1; i++) {
		attach(temp[i].coef, temp[i].expon, D);
	}
	D[count].coef = -1;
	D[count].expon = -1;

	printf("singul_mul - C1(x)\n");
	printf("    coef      expon\n");
	for (int j = 0; j < count; j++) {
		printf("    %.2f\t%d\n", D[j].coef, D[j].expon);
	}
	printf("\n");

	for (int i = 1; A[i].expon != -1; i++)
	{
		polynomial* Ci = (polynomial*)malloc(sizeof(polynomial) * size);

		Ci = single_mul(A[i], B, Ci);

		if (old_count + Ci_count > size) {
			size += 10;
			D = (polynomial*)realloc(D, size * sizeof(polynomial));
			temp = (polynomial*)realloc(temp, size * sizeof(polynomial));
		}

		printf("singul_mul - C%d(x)\n", (i + 1));
		printf("    coef      expon\n");
		for (int j = 0; Ci[j].expon != -1; j++) {
			printf("    %.2f\t%d\n", Ci[j].coef, Ci[j].expon);
		}
		printf("\n");

		//D�� ���� ������ temp�� ����
		int valid_count = 0;
		for (int j = 0; j < count && D[j].expon != -1; j++) {
			temp[j].coef = D[j].coef;
			temp[j].expon = D[j].expon;
			valid_count++;
		}
		temp[valid_count].coef = -1;
		temp[valid_count].expon = -1;

		//count�� ���� old_count�� ��Ƶα�
		int old_count = count;
		count = 0;

		// temp�� Ci�� ���ؼ� D�� ����
		D = padd(temp, Ci, D);
		D[count].coef = -1;
		D[count].expon = -1;

		free(Ci);
	}

	printf("���׽� ���� ��� : D(x)\n");
	printf("    coef      expon\n");
	for (int j = 0; j < count - 1; j++) {
		printf("    %.2f\t%d\n", D[j].coef, D[j].expon);
	}
	printf("\n");


	free(temp);
	return D;
}
