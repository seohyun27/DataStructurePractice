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
polyPointer A, B, C;

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

int main(void)
{
	A = NULL, B = NULL, C = NULL;
	avail = NULL;

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
	printf("���׽� ���� ��� : D(x)");
	C = cpadd(A, B);
	print_polynomial(C);

	return 0;
}