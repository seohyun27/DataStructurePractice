#include <stdio.h>
#include <stdlib.h>

typedef struct node* treePointer;
struct node {   	// Ʈ���� ��� ����
	int key; //���� ����
	double value; //�߰� ������
	struct node* lchild, * rchild;
};

treePointer modified_search(treePointer tree, int key)
{
	treePointer parent = NULL;

	while (tree) {
		if (key == tree->key) //�̹� ������ ��
			return NULL;
		parent = tree;
		if (key < tree->key)
			tree = tree->lchild;
		else
			tree = tree->rchild;
	}
	return parent;
}

void insert(treePointer* node, int key, double value) //���� ���� �� ��Ʈ�� ��ġ�� �ٲ�
{
	treePointer ptr, temp = modified_search(*node, key); //key�� �������� �� ���� ��ġ ���
	
	if (temp || !(*node)) //��ġ �ְų� root�� NULL�̶��
	{
		ptr = (treePointer)malloc(sizeof(struct node));
		ptr->key = key;
		ptr->value = value;
		ptr->lchild = ptr->rchild = NULL; //�ڽ� ��� �ʱ�ȭ

		if (*node)
			if (key < temp->key)	temp->lchild = ptr;
			else temp->rchild = ptr;
		else //root�� �� ����� ��
			*node = ptr;
	}
}

void inorder(treePointer ptr)
{
	if (ptr) //null�� ���� ������
	{
		//���� ������ ���� Ʈ������ ��Ʈ�� ������ �ݺ�
		//print�� ��ġ�� ��ȸ ����� ������ �� ����
		inorder(ptr->lchild);
		printf("%d ", ptr->key);
		inorder(ptr->rchild);
	}
}

//value���� ������ inorder ��ȸ
void inorder_value(treePointer ptr)
{
	if (ptr) //null�� ���� ������
	{
		//���� ������ ���� Ʈ������ ��Ʈ�� ������ �ݺ�
		//print�� ��ġ�� ��ȸ ����� ������ �� ����
		inorder_value(ptr->lchild);
		printf("(%d, %.2f)\t", ptr->key, ptr->value);
		inorder_value(ptr->rchild);
	}
}


int main()
{
	treePointer A = NULL;

	printf("9.1. 12���� (key, value)���� �����Ͽ� ���� Ž�� Ʈ�� ����\n");
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

	printf("inorder ��ȸ ��� : ");
	inorder(A);
	printf("\nvalue�� ������ inorder ��ȸ ��� : ");
	inorder_value(A);
	printf("\n\n");

	return 0;
}