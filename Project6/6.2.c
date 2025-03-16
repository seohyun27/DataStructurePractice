#include <stdio.h>
#include <stdlib.h>
#define ERROR_KEY -999

struct node
{
	int data;
	struct node* next;
};
typedef struct node* nodePointer; //구조체 node의 포인터를 nodePointer로 정의

nodePointer stack, queue, temp, ptr, rear;

void insert_front(nodePointer* A, int data)
{
	//A는 &A로 집어넣어서 *A로 사용
	temp = (nodePointer)malloc(sizeof(*temp));
	temp->data = data;
	temp->next = *A;
	*A = temp;
}

void print_list(nodePointer A)
{
	printf("Head->");
	if (A == NULL) //리스트에 아무것도 존재하지 않을 때
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

	if (*A == NULL) //리스트가 비어있을 때
		*A = temp; //A의 위치 옮겨줘야 함
	else
	{
		ptr = *A;
		while (ptr->next != NULL) //NULL의 바로 앞 node 찾기
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

int delet(nodePointer* A, int data) //마지막 값이 지워질 때 헤더값이 변함
{
	if (*A == NULL) return ERROR_KEY; //배열이 비어있을 때

	if ((*A)->data == data) //첫번째 노드에 값이 존재할 때
		return delet_front(A);

	//삭제할 노드를 찾기
	temp = *A;
	ptr = NULL;
	while (temp != NULL && temp->data != data)
	{
		ptr = temp;
		temp = temp->next;
	}

	if (temp == NULL) return ERROR_KEY; //찾는 노드가 존재하지 않을 때

	int delet_data = temp->data;
	ptr->next = temp->next; //노드 삭제

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
	queue = NULL, rear = NULL;//헤더 초기화
	int select = 0, data;

	while (select != -1)
	{
		printf("리스트로 구현한 스택\n");
		printf("1. push\n");
		printf("2. pop\n");
		printf("-1. exit\n");
		printf("어떤 기능을 수행할까요? : ");
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
			printf("프로그램을 종료합니다.\n\n");
			continue;
		}
		printf("Stack : ");
		print_list(stack);
		printf("\n");
	}

	select = 0; //select 변수 초기화
	while (select != -1)
	{
		printf("리스트로 구현한 큐\n");
		printf("1. addq\n");
		printf("2. deleteq\n");
		printf("-1. exit\n");
		printf("어떤 기능을 수행할까요? : ");
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
			printf("프로그램을 종료합니다.\n");
			continue;
		}
		printf("Queue : ");
		print_list(queue);
		printf("\n");
	}
	return 0;
}