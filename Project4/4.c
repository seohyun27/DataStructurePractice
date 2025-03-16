#include <stdio.h>
#define MAX_STACK_SIZE 10
#define MAX_QUEUE_SIZE 10

int stack[MAX_STACK_SIZE], top = -1;
int queue[MAX_QUEUE_SIZE], front = -1, rear = -1;
int c_queue[MAX_QUEUE_SIZE];

void push(int item)
{
	if (top == MAX_STACK_SIZE - 1)
		printf("The stack is full.\n");
	else
		stack[++top] = item;
}

int pop()
{
	if (top == -1)
	{
		printf("The stack is empty.\n\n");
		return -1;
	}
	return stack[top--];
}

void print_stack()
{
	printf("    index : item\n");
	for (int i = 0; i <= top;i++)
		printf("\t%d : %d\n", i, stack[i]);
	printf("\n");
}

void add_q(int item)
{
	if (rear == MAX_QUEUE_SIZE - 1)
		printf("The queue is full.\n");
	else
		queue[++rear] = item;
}

int delete_q()
{
	if (front == rear)
	{
		printf("The queue is empty.\n\n");
		return -1;
	}
	return queue[++front];
}

void print_q()
{
	printf("    index : item\n");
	for (int i = front + 1; i <= rear;i++)
		printf("\t%d : %d\n", i, queue[i]);
	printf("\n");
}

void add_cq(int item)
{
	if (front == ((rear + 1) % MAX_QUEUE_SIZE))
		printf("The c_queue is full.\n");
	else
	{
		rear = (rear + 1) % MAX_QUEUE_SIZE;
		c_queue[rear] = item;
	}
}

int delete_cq()
{
	if (front == rear)
	{
		printf("The c_queue is empty.\n\n");
		return -1;
	}
	front = (front + 1) % MAX_QUEUE_SIZE;
	return c_queue[front];
}

void print_cq()
{
	printf("    index : item\n");
	int i = (front + 1) % MAX_QUEUE_SIZE;
	while (front != rear)
	{
		printf("\t%d : %d\n", i, c_queue[i]);
		if (i == rear)
			break;
		i = (i + 1) % MAX_QUEUE_SIZE;
	}
	printf("\n");
}

int main(void)
{
	int choice; //switch 문 선택 수
	int num;
	int temp_num;

	printf("4.1. 스택\n");
	while (1)
	{
		printf("스택 - 1.push 2.pop : ");
		scanf_s("%d", &choice);
		if (choice == -1)
			break;
		switch (choice)
		{
		case 1: 
			printf("push item : ");
			scanf_s("%d", &num);
			push(num);
			print_stack();
			break;
		case 2:
			temp_num = pop();
			if (temp_num == -1) break;
			printf("pop item : ");
			printf("%d\n", temp_num);
			print_stack();
			break;
		default:
			printf("잘못된 번호를 입력하였습니다. 다시 입력해주세요.\n\n");
			break;
		}
	}
	printf("\n");

	printf("4.2. 큐\n");
	while (1)
	{
		printf("큐 - 1.addQ 2.deleteQ : ");
		scanf_s("%d", &choice);
		if (choice == -1)
			break;
		switch (choice)
		{
		case 1:
			printf("addQ item : ");
			scanf_s("%d", &num);
			add_q(num);
			print_q();
			break;
		case 2:
			temp_num = delete_q();
			if (temp_num == -1) break;
			printf("pop item : ");
			printf("%d\n", temp_num);
			print_q();
			break;
		default:
			printf("잘못된 번호를 입력하였습니다. 다시 입력해주세요.\n\n");
			break;
		}
	}
	printf("\n");

	front = 4; //front, rear 위치 재설정
	rear = 4;
	printf("4.3. 원형큐\n");
	while (1)
	{
		printf("원형큐 - 1.addCQ 2.deleteCQ : ");
		scanf_s("%d", &choice);
		if (choice == -1)
			break;
		switch (choice)
		{
		case 1:
			printf("addQ item : ");
			scanf_s("%d", &num);
			add_cq(num);
			print_cq();
			break;
		case 2:
			temp_num = delete_cq();
			if (temp_num == -1) break;
			printf("pop item : ");
			printf("%d\n", temp_num);
			print_cq();
			break;
		default:
			printf("잘못된 번호를 입력하였습니다. 다시 입력해주세요.\n\n");
			break;
		}
	}

	return 0;
}