#include <stdio.h>
#include <stdlib.h>
#define COMPARE(x,y) ( ((x)<(y)) ? -1 : ((x)==(y)) ? 0 : 1 )
#define ERROR_KEY -999

struct poly
{
	float coef; //���
	int expon; //����
	struct poly* link;
};
typedef struct poly* polyPointer; //����ü node�� �����͸� nodePointer�� ����

polyPointer avail; //���� ���� ����Ʈ�� first
//�ʿ���� �� ��带 �̰����� �Ű���

polyPointer getNode(void)
//Node �ҷ�����
{
	polyPointer node;
	if (avail) { //avail�� null�� �ƴ϶��
		node = avail; //node�� avail�� ��Ƶα�
		avail = avail->link; //avail �� ĭ �ڷ� �̵�
	}
	else
		node = (polyPointer)malloc(sizeof(*node));
	return node;
}

void retNode(polyPointer node)
//Node ��ȯ�ϱ�
{
	node->link = avail; //node->link�� avail���� �ֱ�
	avail = node; //avail�� node�� ����Ű����
}

void cerease(polyPointer* ptr) //�ּ��� �ּҸ� �Է�
//���׽��� ��°�� avail�� ��ȯ�ϱ�
{
	polyPointer temp;
	if (*ptr) {
		temp = (*ptr)->link; //*ptr�� �������� temp�� ��Ƶ�
		(*ptr)->link = avail; //avail�� *ptr�� �̾���
		avail = temp; //temp�� ��Ƶ� �ּҿ� avail �ű��
		*ptr = NULL; //*ptr�� ������
	}
}

void attach(float coef, int expon, polyPointer head)
//�Ϲ� attach�� �ٸ��� rear�� �ʿ����� ����
{
	polyPointer temp, ptr, ptrb;
	ptrb = head;
	ptr = head->link;

	while (ptr != head) {
		if (ptr->expon < expon) break;
		ptrb = ptr; ptr = ptr->link; //1ĭ �� ������ �̵�
	}
	temp = getNode();
	temp->coef = coef;
	temp->expon = expon;
	temp->link = ptr; //��� �̾��ֱ�
	ptrb->link = temp;
}

polyPointer creat_polynomial() 
//���׾� ���� �Է¹޾� ���� ����Ʈ ť�� ����
{
	polyPointer ptr;
	float coef;
	int expon;

	//������ �� ���� ���� ����Ʈ ptr�� ����� ����
	ptr = getNode();
	ptr->coef = -1; ptr->expon = -1; ptr->link = ptr;

	while (1)
	{
		printf("���׽��� ���� �Է��ϼ���. (coef expon) : ");
		scanf_s("%f %d", &coef, &expon);
		if (expon == -1) break;
		attach(coef, expon, ptr);
	}
	return ptr;
}

void print_polynomial(polyPointer ptr)
//���׽� ���
{
	ptr = ptr->link;
	printf("    coef   expon\n");
	for (;ptr->expon != -1;ptr = ptr->link)
		printf("%8.2f %8d\n", ptr->coef, ptr->expon);
}

polyPointer cpadd(polyPointer a, polyPointer b)
//�� ���׽��� ���ϴ� �Լ�
{
	polyPointer c;
	int sum, done = 0;

	a = a->link;
	b = b->link; //���̳�� �ǳʶ��

	//������ �� ���� ���� ����Ʈ c�� ����� ����
	c = getNode();
	c->coef = -1; c->expon = -1; c->link = c;

	do {
		switch (COMPARE(a->expon, b->expon))
		{
		case -1:
			attach(b->coef, b->expon, c);
			b = b->link;
			break;
		case 0:
			if (a->expon == -1) done = 1;
			else {
				sum = a->coef + b->coef;
				if (sum)
					attach(sum, a->expon, c);
				a = a->link;
				b = b->link;
			}
			break;
		case 1:
			attach(a->coef, a->expon, c);
			a = a->link;
			break;
		}
	} while (!done);
	return c;
}

polyPointer single_mul(struct poly Ai, polyPointer B)
//A�� �� �ϳ��� B�� ���׽��� ���ϴ� �Լ�
{
	float coef;
	int expon;
	polyPointer Mi;
	B = B->link; //���̳�� �ǳʶ��

	Mi = getNode();
	Mi->expon = -1; Mi->expon = -1; Mi->link = Mi;

	while (B->expon != -1) {
		attach(Ai.coef * B->coef, Ai.expon + B->expon, Mi);
		B = B->link;
	}

	return Mi;
}

polyPointer cpmul(polyPointer A, polyPointer B)
//A ���׽İ� B ���׽��� ���ϴ� �Լ�
{
	polyPointer X, D, tempD;
	A = A->link; //���̳�� �ǳʶ��

	D = getNode();
	D->coef = -1; D->expon = -1; D->link = D; //D ���׽��� ���̳�常 �ִ� ���� ����Ʈ�� ����

	int i = 1;
	while (A->expon != -1)
	{
		X = single_mul(*A, B);
		printf("singul_mul - C%d(x)\n", i);
		print_polynomial(X); //�߰� ��� ���

		tempD = cpadd(D, X);
		cerease(&D); //D�� ��ȯ
		D = tempD; //NULL�� �ٲ� D�� tempD�� ����

		cerease(&X);
		A = A->link; //A�� ���� ������ �̵�
		i++;
	}
	return D;
}


int main(void)
{
	polyPointer A, B, C, X, D;
	A = NULL, B = NULL, C = NULL, D = NULL;
	avail = NULL;

	while (1)
	{

		printf("7.1. ���׽� ����\n");
		printf("���׽� A(x)\n");
		A = creat_polynomial();
		printf("���׽� A(x) :\n");
		print_polynomial(A);

		printf("���׽� B(x)\n");
		B = creat_polynomial();
		printf("���׽� B(x) :\n");
		print_polynomial(B);

		printf("7.2 ���׽� ����\n");
		printf("���׽� ���� ��� : D(x)\n");
		C = cpadd(A, B);
		print_polynomial(C);

		printf("7.3 ���׽� ����\n");
		D = cpmul(A, B);
		printf("���׽� ���� ��� : D(x)\n");
		print_polynomial(D);

		cerease(&A);
		cerease(&B);
		cerease(&C);
		cerease(&D);

		printf("\n");
	}

	return 0;
}