#include <stdio.h>
#include <stdlib.h>

struct node {
	char data;
	struct node* lchild, * rchild;
};
typedef struct node* NodePointer;

NodePointer make_node(int n)
{
	NodePointer temp = (NodePointer)malloc(sizeof(struct node)); //공간 할당
	temp->data = n; //데이터 삽입
	temp->lchild = temp->rchild = NULL; //자식 노드들 초기화
	return temp;
}

NodePointer make_tree_by_code()
{
	NodePointer root;
	root = make_node(5);
	root->lchild = make_node(3);
	root->rchild = make_node(8);
	root->lchild->lchild = make_node(1);
	root->lchild->rchild = make_node(4);

	return root;
}

void inorder(NodePointer ptr)
{
	if (ptr) //null을 만날 때까지
	{
		//왼쪽 오른쪽 서브 트리에서 루트의 과정을 반복
		//print의 위치로 순회 방식을 선택할 수 있음
		inorder(ptr->lchild);
		printf("%d ", ptr->data);
		inorder(ptr->rchild);
	}
}

void preorder(NodePointer ptr)
{
	if (ptr)
	{
		printf("%d ", ptr->data);
		preorder(ptr->lchild);
		preorder(ptr->rchild);
	}
}

void postorder(NodePointer ptr)
{
	if (ptr)
	{
		postorder(ptr->lchild);
		postorder(ptr->rchild);
		printf("%d ", ptr->data);
	}
}

NodePointer copy(NodePointer origin)
{
	NodePointer temp;

	if (origin) {
		NodePointer temp = (NodePointer)malloc(sizeof(struct node));
		temp->lchild = copy(origin->lchild); //왼쪽 방향의 link를 다 연결
		temp->rchild = copy(origin->rchild); //오른쪽 방향의 link를 다 연결
		temp->data = origin->data; //양쪽 재귀가 다 끝나야 데이터를 담을 수 있음
		return temp;
	}
	return NULL;
}

int equal(NodePointer fisrt, NodePointer second)
{
	//only return으로만 이루어진 함수
	return((!fisrt && !second) || // 1. fisrt와 second의 노드 둘 다 존재하지 않거나
		// 2. 둘 다 노드 존재하면서 노드 안의 값이 같고
		(fisrt && second && (fisrt->data == second->data) &&
			//왼쪽과 오른쪽에서도 동일하게 진행 될 때
			equal(fisrt->lchild, second->lchild) &&
			equal(fisrt->rchild, second->rchild)));
}

NodePointer swap(NodePointer origin)
{
	NodePointer temp;

	if (origin) {
		NodePointer temp = (NodePointer)malloc(sizeof(struct node));
		temp->rchild = swap(origin->lchild); //오른쪽 방향의 link를 다 왼쪽으로 연결
		temp->lchild = swap(origin->rchild); //왼쪽 방향의 link를 다 오른쪽으로 연결
		temp->data = origin->data; //양쪽 재귀가 다 끝나고 데이터 담기
		return temp;
	}
	return NULL;
}

int main(void)
{
	NodePointer A, B, C;
	int result;

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

	return 0;
}
