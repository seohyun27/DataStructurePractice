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

int main(void)
{
	printf("8.1.1. 트리 구성 (A = make_tree_by_code())\n");
	NodePointer A = make_tree_by_code();
	
	printf("8.1.2.트리 순회(A)\n");
	printf("inorder(A) : ");
	inorder(A);
	printf("\n");

	printf("preorder(A) : ");
	preorder(A);
	printf("\n");
	
	printf("postorder(A) : ");
	postorder(A);
	printf("\n");

	return 0;
}
