#include <stdio.h>
#include <stdlib.h>
#define ERROR_KEY -999

struct node
{
	int data;
	struct node* next;
};
typedef struct node* nodePointer; //����ü node�� �����͸� nodePointer�� ����

nodePointer A, temp, ptr;

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

int search(nodePointer A, int data)
{
	int count = 0;
	while (A != NULL)
	{
		if (A->data == data) return count;
		A = A->next;
		count += 1;
	}

	return ERROR_KEY;
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

nodePointer invert(nodePointer A)
{
	//A�� lead, ptr�� middle, temp�� tail�� ���
	//lead, middle, tail�� �̿��� �������� ����� ����Ʈ�� ù ��° �ּ� ��ȯ
	ptr = NULL;
	while (A) {
		temp = ptr;
		ptr = A;
		A = A->next; //A, ptr, temp ������ �� ���� �̵�
		ptr->next = temp; //��ũ �Ųٷ� ����
	}
	return ptr; //������� ���� ����Ʈ�� first �ּ� ��ȯ
}



int main()
{
	A = NULL; //��� �ʱ�ȭ

	while (1)
	{
		int select, data, delete_data, node_num;

		printf("����Ʈ �⺻����\n");
		printf("0. print list\n");
		printf("1. insert_front\n");
		printf("2. insert_last\n");
		printf("3. delete_front\n");
		printf("4. delete_\n");
		printf("5. search\n");
		printf("6. invert\n");
		printf("-1. exit\n");
		printf("� ����� �����ұ��? : ");
		scanf_s("%d", &select);

		switch (select)
		{
		case 0:
			break;
		case 1:
			printf("������ : ");
			scanf_s("%d", &data);
			insert_front(&A, data);
			break;
		case 2:
			printf("������ : ");
			scanf_s("%d", &data);
			insert_last(&A, data);
			break;
		case 3:
			delete_data = delet_front(&A);
			printf("���� ������ : %d\n", delete_data);
			break;
		case 4:
			printf("������ : ");
			scanf_s("%d", &data);
			delete_data = delet(&A, data);
			printf("���� ������ : %d\n", delete_data);
			break;
		case 5:
			printf("������ : ");
			scanf_s("%d", &data);
			node_num = search(A, data);
			printf("��� ��ȣ : %d\n", node_num);
			break;
		case 6:
			A = invert(A);
			break;
		case -1:
			printf("���α׷��� �����մϴ�.\n");
			exit(0);
		}
		printf("����Ʈ : ");
		print_list(A);
		printf("\n");
	}
	return 0;
}