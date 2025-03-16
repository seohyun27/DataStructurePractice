#include <stdio.h>
#include <stdlib.h>
#define ERROR_KEY -999

struct node
{
	int data;
	struct node* next;
};
typedef struct node* nodePointer; //구조체 node의 포인터를 nodePointer로 정의

nodePointer A, temp, ptr;

void insert_front(nodePointer *A, int data)
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

void insert_last(nodePointer *A, int data)
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





int main()
{
	A = NULL; //헤더 초기화

	while (1)
	{
		int select, data, delete_data, node_num;

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
			printf("프로그램을 종료합니다.\n");
			exit(0);
		}
		printf("리스트 : ");
		print_list(A);
		printf("\n");
	}
	return 0;
}