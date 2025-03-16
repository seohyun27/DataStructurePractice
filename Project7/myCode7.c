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

polyPointer creat_polynomial() //���׾� ���� �Է¹޾� ť�� ����
{
	polyPointer temp, first, rear;
	float coef;
	int expon;

	first = getNode();
	first->coef = -1;
	first->expon = -1;
	rear = first;

	while (1)
	{
		printf("���׽��� ���� �Է��ϼ���. (coef expon) : ");
		scanf_s("%f %d", &coef, &expon);
		if (expon == -1) break;

		//�̸� ��带 �հ� attach�ϴ� ��� ����

		temp = getNode();
		temp->coef = coef;
		temp->expon = expon;
		temp->link = NULL;

		if (first->link)
			rear->link = temp;
		else
			first->link = temp;
		rear = temp;
	}
	rear->link = first; //����� �� ��� �̾��ֱ�

	return first;
}

void attach(float coef, int expon, polyPointer* ptr) //ptr = rear
{
	polyPointer temp;
	temp = getNode();

	temp->coef = coef;
	temp->expon = expon;
	(*ptr)->link = temp; //rear�̿��ؼ� �ڷ� �̾��ֱ�
	*ptr = temp;
}

void print_polynomial(polyPointer ptr)
{
	ptr = ptr->link;
	printf("    coef   expon\n");
	for (;ptr->expon != -1;ptr = ptr->link)
		printf("%8.2f %8d\n", ptr->coef, ptr->expon);
}

polyPointer cpadd(polyPointer a, polyPointer b)
{
	polyPointer startA, c, lastC;
	int sum, done = 0;
	startA = a; //a�� ���۳�� ���

	a = a->link;
	b = b->link; //���̳�� �ǳʶ��

	c = getNode();
	c->expon = -1;
	lastC = c; //c�� ���̳��

	do {
		switch (COMPARE(a->expon, b->expon))
		{
		case -1:
			attach(b->coef, b->expon, &lastC);
			b = b->link;
			break;
		case 0:
			if (startA == a) done = 1;
			else {
				sum = a->coef + b->coef;
				if (sum)
					attach(sum, a->expon, &lastC);
				a = a->link;
				b = b->link;
			}
			break;
		case 1:
			attach(a->coef, a->expon, &lastC);
			a = a->link;
			break;
		}
	} while (!done);
	lastC->link = c; //last�� ù ��� �̾��ֱ�
	return c;
}

polyPointer single_mul(struct poly Ai, polyPointer B)
//A�� �� �ϳ��� B�� ���׽��� ���ϴ� �Լ�
{
	float coef;
	int expon;
	polyPointer startB, X, lastX;
	startB = B;
	B = B->link; //���̳�� �ǳʶ��

	X = getNode();
	X->expon = -1;
	lastX = X; //x�� ���̳��

	while (B != startB) {
		coef = Ai.coef * B->coef;
		expon = Ai.expon + B->expon;
		attach(coef, expon, &lastX);
		B = B->link;
	}

	lastX->link = X; //last�� ù ��� �̾��ֱ�
	return X;
}

polyPointer cpmul(polyPointer A, polyPointer B)
//A ���׽İ� B ���׽��� ���ϴ� �Լ�
{
	polyPointer X, D, tempD, startA;
	startA = A;
	A = A->link; //���̳�� �ǳʶ��

	D = getNode();
	D->expon = -1;
	D->link = D; //D ���׽��� ���̳�常 �ִ� ���� ����Ʈ�� ����

	int i = 1;
	while (A != startA)
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
	A = NULL, B = NULL, C =NULL, D = NULL;
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