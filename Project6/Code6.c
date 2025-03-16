#include <stdio.h>
#include <stdlib.h>
#define ERROR_KEY -999

struct node
{
	int data;
	struct node* next;
};
typedef struct node* nodePointer; //����ü node�� �����͸� nodePointer�� ����

nodePointer stack = NULL, queue = NULL;

void list_free(nodePointer* A)
{
	nodePointer ptr = NULL; //���� �� �ʱ�ȭ
	nodePointer temp = (*A);
	while (temp) {
		ptr = temp;
		temp = temp->next;
		free(ptr);
	}
	(*A) = NULL;
}

void print_list(nodePointer A)
{
	printf("Head->");

	while (A != NULL)
	{
		printf("%d", A->data);
		A = A->next;
		printf("->");
	}
	printf("Null\n");
}

void insert_front(nodePointer* A, int data)
{
	//A�� &A�� ����־ *A�� ���
	nodePointer temp = NULL;
	temp = (nodePointer)malloc(sizeof(*temp));
	temp->data = data;
	if (*A)
		temp->next = *A;
	else
		temp->next = NULL;
	*A = temp;
}

void insert_last(nodePointer* A, int data)
{
	nodePointer temp = NULL, ptr = NULL;
	temp = (nodePointer)malloc(sizeof(*temp));
	temp->data = data;
	temp->next = NULL;

	if (*A) //����� null�ƴ� ��
	{
		for (ptr = *A;ptr->next;ptr = ptr->next);
		//���� ���� for��
		//ptr ��ġ �Űܰ��鼭 NULL�� �ٷ� �� node ã��
		ptr->next = temp;
	}
	else //����Ʈ�� ������� ��
		*A = temp; //A�� ��ġ �Ű���� ��
}

int search(nodePointer A, int data)
{
	int count = 0;
	for(;A;A = A->next, count++)
		if (A->data == data) return count; //��ġ�ϴ� ������ �ִٸ� count ����
	return ERROR_KEY;
}

int delet_front(nodePointer* A)
{
	nodePointer ptr = (*A);
	int data;
	
	if (ptr) { //*A�� NULL�ƴ϶��
		data = (*A)->data;
		(*A) = (*A)->next;
		free(ptr); //�ʿ���� ���� ����
		return data;
	}

	return ERROR_KEY; //*A�� NULL�̶�� ���� Ű ����
}

int delet(nodePointer* A, int data) //������ ���� ������ �� ������� ����
{
	nodePointer ptr = NULL, ptrb = NULL;
	int value;

	for (ptr = (*A); ptr; ptrb = ptr, ptr = ptr->next) {
		//ptr�� NULL, ptrb�� NULL�� �ٷ� ���� �ּҸ� ���� ������
		if (ptr->next == data) {
			//��ġ�ϴ� data �����Ѵٸ�
			value = ptr->data;
			if (ptrb)
				ptrb->next = ptr->next;
			else //���� �� �� �ϳ��� ��常 ������ ��
				(*A) = ptr->next;
			free(ptr); //�ʿ� ������ ��� ������ ����
			return value;
		}
	}
	return ERROR_KEY; //��ġ�ϴ� data ���� ��
}

nodePointer invert(nodePointer* A)
{
	nodePointer temp = (*A); //���� ����Ʈ temp�� ���
	(*A) = NULL; //A����Ʈ ����
	while (temp)
		insert_front(A, delet_front(&temp));
	//�ٽ� A�� �����鼭 �������� ��ȯ
}

//merge �Լ��� merge.c ���Ͽ� ���� ���� ��Ĵ�� ��� ����!


//������ top�� front, rear ���̵� ���ð� ť�� � ����
void push(int data)
{
	insert_front(&stack, data);
}

int pop()
{
	return delet_front(&stack);
	//delet_front���� ��ȯ�� data�� ERROR_KEY�� ��� �״�� ��ȯ�� 
}

void add(int data)
{
	insert_last(&queue, data);
}

int delete()
{
	return delet_front(&queue);
}

int main()
{
	nodePointer A = NULL; //��� �ʱ�ȭ
	int select = 0, data, delete_data, node_num;

	while (select != -1)
	{
		printf("����Ʈ �⺻����\n");
		printf("0. print list\n");
		printf("1. insert_front\n");
		printf("2. insert_last\n");
		printf("3. delete_front\n");
		printf("4. delete_\n");
		printf("5. search\n");
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
		case -1:
			printf("���α׷��� �����մϴ�.\n\n");
			continue;
		}
		printf("����Ʈ : ");
		print_list(A);
		printf("\n");
	}
	

	select = 0; //select �ʱ�ȭ
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
			printf("���α׷��� �����մϴ�.\n\n");
			continue;
		}
		printf("Queue : ");
		print_list(queue);
		printf("\n");
	}
	return 0;
}