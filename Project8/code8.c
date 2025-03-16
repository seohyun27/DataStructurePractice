#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node {
	char data;
	struct node* lchild, * rchild;
};
typedef struct node* NodePointer;

NodePointer make_node(int n)
//새로운 노드를 생성
{
	NodePointer temp = (NodePointer)malloc(sizeof(struct node)); //공간 할당
	temp->data = n; //데이터 삽입
	temp->lchild = temp->rchild = NULL; //자식 노드들 초기화
	return temp;
}

NodePointer make_tree_by_code()
//트리를 생성하는 함수
//직접 이어붙임
{
	NodePointer root = NULL;
	root = make_node(5);
	root->lchild = make_node(3);
	root->rchild = make_node(8);
	root->lchild->lchild = make_node(1);
	root->lchild->rchild = make_node(4);

	return root;
}

void inorder(NodePointer ptr)
//중위 순회 알고리즘
{
	if (ptr) //null을 만날 때까지
	{
		//재귀 함수
		//왼쪽 오른쪽 서브 트리에서 루트의 과정을 반복
		//print의 위치로 순회 방식을 선택할 수 있음
		inorder(ptr->lchild);
		printf("%d ", ptr->data);
		inorder(ptr->rchild);
	}
}

void preorder(NodePointer ptr)
//전위 순회 알고리즘
{
	if (ptr)
	{
		printf("%d ", ptr->data);
		preorder(ptr->lchild);
		preorder(ptr->rchild);
	}
}

void postorder(NodePointer ptr)
//후위 순회 알고리즘
{
	if (ptr)
	{
		postorder(ptr->lchild);
		postorder(ptr->rchild);
		printf("%d ", ptr->data);
	}
}

NodePointer copy(NodePointer origin)
//트리 복사
{
	NodePointer temp = NULL; //NULL집어넣어 두고 시작

	if (origin) {
		NodePointer temp = (NodePointer)malloc(sizeof(struct node));
		temp->lchild = copy(origin->lchild); //왼쪽 방향의 link를 다 연결
		temp->rchild = copy(origin->rchild); //오른쪽 방향의 link를 다 연결
		temp->data = origin->data; //양쪽 재귀가 다 끝나야 데이터를 담을 수 있음
		return temp;
	}
	return temp;
}

NodePointer swap(NodePointer origin)
//트리 반전
{
	NodePointer temp = NULL;

	if (origin) {
		NodePointer temp = (NodePointer)malloc(sizeof(struct node));
		temp->rchild = swap(origin->lchild); //오른쪽 방향의 link를 다 왼쪽으로 연결
		temp->lchild = swap(origin->rchild); //왼쪽 방향의 link를 다 오른쪽으로 연결
		temp->data = origin->data; //양쪽 재귀가 다 끝나고 데이터 담기
		return temp;
	}
	return temp; //null을 리턴하는 대신 처음에 temp에 null을 담아두고 리턴도 가능
}

int equal(NodePointer fisrt, NodePointer second)
//트리 동질성 검사
{
	//only return으로만 이루어진 함수
	return((!fisrt && !second) ||
		// 1. fisrt와 second의 노드 둘 다 null일 때(리프 노드의 자식들에서 성립)
		// 2. 둘 다 노드 존재하면서 노드 안의 값이 같고
		(fisrt && second && (fisrt->data == second->data) &&
			//자식들에게서도 동일하게 진행 될 때
			equal(fisrt->lchild, second->lchild) &&
			equal(fisrt->rchild, second->rchild)));
}

NodePointer make_random_tree(int n)
//1~n값이 들어간 랜덤 이진 트리 생성
{
	NodePointer root, temp, parent_temp;

	temp = make_node(1); //루트 노드 생성
	root = temp; //루트 노드의 위치를 root에 저장해둘 것

	srand(time(NULL)); //랜덤 시드값 초기화

	for (int i = 2; i <= n;i++)
	{
		temp = root; //temp의 위치 리셋

		while (1)
		{
			if (rand() % 2 == 0)
			{
				parent_temp = temp;
				temp = temp->lchild;
				if(!temp) 
				//자리 비어 있다면 그 자리에 집어넣고 while문 탈출
				//아니라면 while문 반복
				{
					temp = make_node(i);
					parent_temp->lchild = temp;
					break;
				}
			}
			else
			{
				parent_temp = temp;
				temp = temp->rchild;
				if (!temp)
				{
					temp = make_node(i);
					parent_temp->rchild = temp;
					break;
				}
			}

			/*
			rand() 이용해 왼/오 랜덤으로 내려가기
			temp == null 확인
			맞다면 새 노드 생성, while문 break;
			아니라면 다시 while문 반복 -> rand()값 뽑기
			*/
		}
	}
	return root; //만들어진 트리 반환
}


int main(void)
{
	NodePointer A, B, C, D;
	int result, n;

	printf("8.1.1. 트리 구성 (A = make_tree_by_code())\n");
	A = make_tree_by_code();
	printf("8.1.2.트리 순회(A)\n");
	printf("inorder(A) : ");
	inorder(A);
	printf("\n");
	printf("preorder(A) : ");
	preorder(A);
	printf("\n");
	printf("postorder(A) : ");
	postorder(A);
	printf("\n\n");

	printf("8.2.1.트리 복사(B = copy(A))\n");
	B = copy(A);
	printf("8.2.2.트리 순회 (B)\n");
	printf("inorder(B) : ");
	inorder(B);
	printf("\n");
	printf("preorder(B) : ");
	preorder(B);
	printf("\n");
	printf("postorder(B) : ");
	postorder(B);
	printf("\n\n");

	printf("8.2.3.트리 동질성 검사(equal(A, B)\n");
	result = equal(A, B);
	printf("equal(A, B) : ");
	if (result)
		printf("TRUE\n\n");
	else
		printf("FALSE\n\n");

	printf("8.2.4. 트리 swap (C = swap(A))\n");
	C = swap(A);
	printf("8.2.5. 트리 순회 (C)\n");
	printf("inorder(C) : ");
	inorder(C);
	printf("\n");
	printf("preorder(C) : ");
	preorder(C);
	printf("\n");
	printf("postorder(C) : ");
	postorder(C);
	printf("\n\n");

	printf("8.3.1. 랜덤 트리 자동 생성 (D)\n");
	printf("Input n : ");
	scanf_s("%d", &n);
	D = make_random_tree(n);
	printf("8.3.2. 트리 순회 (D)\n");
	printf("inorder(D) : ");
	inorder(D);
	printf("\n");
	printf("preorder(D) : ");
	preorder(D);
	printf("\n");
	printf("postorder(D) : ");
	postorder(D);
	printf("\n\n");

	return 0;
}
