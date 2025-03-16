#include <stdio.h>
#include <stdlib.h>
#define ERROR_KEY -999
#define COMPARE(x,y) (((x)<(y))?-1:((x)==(y))?0:1)

struct node
{
	int data;
	struct node* next;
};
typedef struct node* nodePointer; //구조체 node의 포인터를 nodePointer로 정의

nodePointer A, B, C, temp, ptr;

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


//자료구조 교재 4장 25페이지
//다항식 더하기와 원리 같음 -> 계수 지수 없고 data만 존재
nodePointer merge(nodePointer A, nodePointer B)
{
	while(A&&B) //A나 B 중 하나가 null이 될 때까지
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

	//남은 데이터 처리
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
	C = NULL;//헤더 초기화
	int data;

	while (1)
	{
		printf("A의 데이터 입력(오름차순) : ");
		scanf_s("%d", &data);
		if (data == -1) break;
		insert_last(&A, data);
	}
	printf("A 리스트 : ");
	print_list(A);
	printf("\n");

	while (1)
	{
		printf("B의 데이터 입력(오름차순) : ");
		scanf_s("%d", &data);
		if (data == -1) break;
		insert_last(&B, data);
	}
	printf("B 리스트 : ");
	print_list(B);
	printf("\n");

	C = merge(A, B);
	printf("C 리스트 : ");
	print_list(C);
	printf("\n");

	return 0;
}