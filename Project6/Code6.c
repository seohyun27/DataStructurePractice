#include <stdio.h>
#include <stdlib.h>
#define ERROR_KEY -999

struct node
{
	int data;
	struct node* next;
};
typedef struct node* nodePointer; //구조체 node의 포인터를 nodePointer로 정의

nodePointer stack = NULL, queue = NULL;

void list_free(nodePointer* A)
{
	nodePointer ptr = NULL; //선언 및 초기화
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
	//A는 &A로 집어넣어서 *A로 사용
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

	if (*A) //헤더가 null아닐 때
	{
		for (ptr = *A;ptr->next;ptr = ptr->next);
		//내용 없는 for문
		//ptr 위치 옮겨가면서 NULL의 바로 앞 node 찾기
		ptr->next = temp;
	}
	else //리스트가 비어있을 때
		*A = temp; //A의 위치 옮겨줘야 함
}

int search(nodePointer A, int data)
{
	int count = 0;
	for(;A;A = A->next, count++)
		if (A->data == data) return count; //일치하는 데이터 있다면 count 리턴
	return ERROR_KEY;
}

int delet_front(nodePointer* A)
{
	nodePointer ptr = (*A);
	int data;
	
	if (ptr) { //*A가 NULL아니라면
		data = (*A)->data;
		(*A) = (*A)->next;
		free(ptr); //필요없는 공간 제거
		return data;
	}

	return ERROR_KEY; //*A가 NULL이라면 에러 키 리턴
}

int delet(nodePointer* A, int data) //마지막 값이 지워질 때 헤더값이 변함
{
	nodePointer ptr = NULL, ptrb = NULL;
	int value;

	for (ptr = (*A); ptr; ptrb = ptr, ptr = ptr->next) {
		//ptr이 NULL, ptrb가 NULL의 바로 앞의 주소를 가질 때까지
		if (ptr->next == data) {
			//일치하는 data 존재한다면
			value = ptr->data;
			if (ptrb)
				ptrb->next = ptr->next;
			else //삭제 후 단 하나의 노드만 존재할 때
				(*A) = ptr->next;
			free(ptr); //필요 없어진 노드 데이터 삭제
			return value;
		}
	}
	return ERROR_KEY; //일치하는 data 없을 때
}

nodePointer invert(nodePointer* A)
{
	nodePointer temp = (*A); //원래 리스트 temp에 담기
	(*A) = NULL; //A리스트 비우기
	while (temp)
		insert_front(A, delet_front(&temp));
	//다시 A에 담으면서 역순으로 교환
}

//merge 함수는 merge.c 파일에 내가 만든 방식대로 담겨 있음!


//별도의 top과 front, rear 없이도 스택과 큐를 운영 가능
void push(int data)
{
	insert_front(&stack, data);
}

int pop()
{
	return delet_front(&stack);
	//delet_front에서 반환한 data가 ERROR_KEY일 경우 그대로 반환됨 
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
	nodePointer A = NULL; //헤더 초기화
	int select = 0, data, delete_data, node_num;

	while (select != -1)
	{
		printf("리스트 기본연산\n");
		printf("0. print list\n");
		printf("1. insert_front\n");
		printf("2. insert_last\n");
		printf("3. delete_front\n");
		printf("4. delete_\n");
		printf("5. search\n");
		printf("-1. exit\n");
		printf("어떤 기능을 수행할까요? : ");
		scanf_s("%d", &select);

		switch (select)
		{
		case 0:
			break;
		case 1:
			printf("데이터 : ");
			scanf_s("%d", &data);
			insert_front(&A, data);
			break;
		case 2:
			printf("데이터 : ");
			scanf_s("%d", &data);
			insert_last(&A, data);
			break;
		case 3:
			delete_data = delet_front(&A);
			printf("삭제 데이터 : %d\n", delete_data);
			break;
		case 4:
			printf("데이터 : ");
			scanf_s("%d", &data);
			delete_data = delet(&A, data);
			printf("삭제 데이터 : %d\n", delete_data);
			break;
		case 5:
			printf("데이터 : ");
			scanf_s("%d", &data);
			node_num = search(A, data);
			printf("노드 번호 : %d\n", node_num);
			break;
		case -1:
			printf("프로그램을 종료합니다.\n\n");
			continue;
		}
		printf("리스트 : ");
		print_list(A);
		printf("\n");
	}
	

	select = 0; //select 초기화
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
			printf("프로그램을 종료합니다.\n\n");
			continue;
		}
		printf("Queue : ");
		print_list(queue);
		printf("\n");
	}
	return 0;
}