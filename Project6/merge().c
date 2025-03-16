#include <stdio.h>
#include <stdlib.h>
#define ERROR_KEY -999
#define COMPARE(x,y) (((x)<(y))?-1:((x)==(y))?0:1)

struct node
{
	int data;
	struct node* next;
};
typedef struct node* nodePointer; //����ü node�� �����͸� nodePointer�� ����

nodePointer A, B, C, temp, ptr;

void insert_front(nodePointer* A, int data)
{
	//A�� &A�� ����־ *A�� ���
	temp = (nodePointer)malloc(sizeof(*temp));
	temp->data = data;
	temp->next = *A;
	*A = temp;
}

void print_list(nodePointer A)
{
	printf("Head->");
	if (A == NULL) //����Ʈ�� �ƹ��͵� �������� ���� ��
	{
		printf("Null\n");
		return 0;
	}

	while (A != NULL)
	{
		printf("%d", A->data);
		A = A->next;
		printf("->");
		if (A == NULL) printf("Null\n");
	}
}

void insert_last(nodePointer* A, int data)
{
	temp = (nodePointer)malloc(sizeof(*temp));
	temp->data = data;
	temp->next = NULL;

	if (*A == NULL) //����Ʈ�� ������� ��
		*A = temp; //A�� ��ġ �Ű���� ��
	else
	{
		ptr = *A;
		while (ptr->next != NULL) //NULL�� �ٷ� �� node ã��
			ptr = ptr->next;
		ptr->next = temp;
	}
}

int delet_front(nodePointer* A)
{
	if (*A == NULL) return ERROR_KEY;

	int data = (*A)->data;
	(*A) = (*A)->next;

	return data;
}

int delet(nodePointer* A, int data) //������ ���� ������ �� ������� ����
{
	if (*A == NULL) return ERROR_KEY; //�迭�� ������� ��

	if ((*A)->data == data) //ù��° ��忡 ���� ������ ��
		return delet_front(A);

	//������ ��带 ã��
	temp = *A;
	ptr = NULL;
	while (temp != NULL && temp->data != data)
	{
		ptr = temp;
		temp = temp->next;
	}

	if (temp == NULL) return ERROR_KEY; //ã�� ��尡 �������� ���� ��

	int delet_data = temp->data;
	ptr->next = temp->next; //��� ����

	return delet_data;
}


//�ڷᱸ�� ���� 4�� 25������
//���׽� ���ϱ�� ���� ���� -> ��� ���� ���� data�� ����
nodePointer merge(nodePointer A, nodePointer B)
{
	while(A&&B) //A�� B �� �ϳ��� null�� �� ������
		switch (COMPARE(A->data, B->data))
		{
		case -1: //if (A->data < B->data)
			insert_last(&C, A->data);
			A = A->next;
			break;
		case 0:
			insert_last(&C, A->data);
			insert_last(&C, B->data);
			A = A->next;
			B = B->next;
			break;
		case 1:
			insert_last(&C, B->data);
			B = B->next;
			break;
		}

	//���� ������ ó��
	while (A) {
		insert_last(&C, A->data);
		A = A->next;
	}

	while (B) {
		insert_last(&C, B->data);
		B = B->next;
	}

	return C;
}


int main()
{
	A = NULL;
	B = NULL;
	C = NULL;//��� �ʱ�ȭ
	int data;

	while (1)
	{
		printf("A�� ������ �Է�(��������) : ");
		scanf_s("%d", &data);
		if (data == -1) break;
		insert_last(&A, data);
	}
	printf("A ����Ʈ : ");
	print_list(A);
	printf("\n");

	while (1)
	{
		printf("B�� ������ �Է�(��������) : ");
		scanf_s("%d", &data);
		if (data == -1) break;
		insert_last(&B, data);
	}
	printf("B ����Ʈ : ");
	print_list(B);
	printf("\n");

	C = merge(A, B);
	printf("C ����Ʈ : ");
	print_list(C);
	printf("\n");

	return 0;
}