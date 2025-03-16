#include <stdio.h>
#include <stdlib.h>
#define ERROR_KEY -999

struct node
{
	int data;
	struct node* next;
};
typedef struct node* nodePointer; //����ü node�� �����͸� nodePointer�� ����

nodePointer stack, queue, temp, ptr, rear;

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

void push(int data)
{
	insert_front(&stack, data);
}

int pop()
{
	int data = delet_front(&stack);
	if (data == ERROR_KEY)
		return ERROR_KEY;
	return data;
}

void add(int data)
{
	insert_last(&queue, data);
	rear = temp;
}

int delete()
{
	int data = delet_front(&queue);
	if (data == ERROR_KEY)
		return ERROR_KEY;
	return data;
}

int main()
{
	stack = NULL;
	queue = NULL, rear = NULL;//��� �ʱ�ȭ
	int select = 0, data;

	while (select != -1)
	{
		printf("����Ʈ�� ������ ����\n");
		printf("1. push\n");
		printf("2. pop\n");
		printf("-1. exit\n");
		printf("� ����� �����ұ��? : ");
		scanf_s("%d", &select);

		switch (select)
		{
		case 1:
			printf("push item : ");
			scanf_s("%d", &data);
			push(data);
			break;
		case 2:
			data = pop();
			printf("pop item : %d\n", data);
			break;
		case -1:
			printf("���α׷��� �����մϴ�.\n\n");
			continue;
		}
		printf("Stack : ");
		print_list(stack);
		printf("\n");
	}

	select = 0; //select ���� �ʱ�ȭ
	while (select != -1)
	{
		printf("����Ʈ�� ������ ť\n");
		printf("1. addq\n");
		printf("2. deleteq\n");
		printf("-1. exit\n");
		printf("� ����� �����ұ��? : ");
		scanf_s("%d", &select);

		switch (select)
		{
		case 1:
			printf("addq item :");
			scanf_s("%d", &data);
			add(data);
			break;
		case 2:
			data = delete();
			printf("deleteq item : %d\n", data);
			break;
		case -1:
			printf("���α׷��� �����մϴ�.\n");
			continue;
		}
		printf("Queue : ");
		print_list(queue);
		printf("\n");
	}
	return 0;
}