#include <stdio.h>
#include <stdlib.h>

typedef struct node* treePointer;
struct node {   	// 트리의 노드 구조
	int key; //정렬 기준
	double value; //추가 데이터
	struct node* lchild, * rchild;
};

treePointer modified_search(treePointer tree, int key)
{
	treePointer parent = NULL;

	while (tree) {
		if (key == tree->key) //이미 존재할 때
			return NULL;
		parent = tree;
		if (key < tree->key)
			tree = tree->lchild;
		else
			tree = tree->rchild;
	}
	return parent;
}

void insert(treePointer* node, int key, double value) //최초 생성 시 루트의 위치가 바뀜
{
	treePointer ptr, temp = modified_search(*node, key); //key를 기준으로 한 삽입 위치 잡기
	
	if (temp || !(*node)) //위치 있거나 root가 NULL이라면
	{
		ptr = (treePointer)malloc(sizeof(struct node));
		ptr->key = key;
		ptr->value = value;
		ptr->lchild = ptr->rchild = NULL; //자식 노드 초기화

		if (*node)
			if (key < temp->key)	temp->lchild = ptr;
			else temp->rchild = ptr;
		else //root가 빈 노드일 때
			*node = ptr;
	}
}

void inorder(treePointer ptr)
{
	if (ptr) //null을 만날 때까지
	{
		//왼쪽 오른쪽 서브 트리에서 루트의 과정을 반복
		//print의 위치로 순회 방식을 선택할 수 있음
		inorder(ptr->lchild);
		printf("%d ", ptr->key);
		inorder(ptr->rchild);
	}
}

//value값을 포함한 inorder 순회
void inorder_value(treePointer ptr)
{
	if (ptr) //null을 만날 때까지
	{
		//왼쪽 오른쪽 서브 트리에서 루트의 과정을 반복
		//print의 위치로 순회 방식을 선택할 수 있음
		inorder_value(ptr->lchild);
		printf("(%d, %.2f)\t", ptr->key, ptr->value);
		inorder_value(ptr->rchild);
	}
}


int main()
{
	treePointer A = NULL;

	printf("9.1. 12개의 (key, value)쌍을 생성하여 이진 탐색 트리 생성\n");
	insert(&A, 10, (1.0 / 10));
	insert(&A, 6, (1.0 / 6));
	insert(&A, 15, (1.0 / 15));
	insert(&A, 8, (1.0 / 8));
	insert(&A, 18, (1.0 / 18));
	insert(&A, 12, (1.0 / 12));
	insert(&A, 3, (1.0 / 3));
	insert(&A, 14, (1.0 / 14));
	insert(&A, 9, (1.0 / 9));
	insert(&A, 20, (1.0 / 20));
	insert(&A, 5, (1.0 / 5));
	insert(&A, 2, (1.0 / 2));

	printf("inorder 순회 결과 : ");
	inorder(A);
	printf("\nvalue를 포함한 inorder 순회 결과 : ");
	inorder_value(A);
	printf("\n\n");

	return 0;
}