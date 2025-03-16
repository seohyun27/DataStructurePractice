#include <stdio.h>
#include <stdlib.h>

struct node {
	char data;
	struct node* lchild, * rchild;
};
typedef struct node* NodePointer;

NodePointer make_node(int n)
{
	NodePointer temp = (NodePointer)malloc(sizeof(struct node)); //���� �Ҵ�
	temp->data = n; //������ ����
	temp->lchild = temp->rchild = NULL; //�ڽ� ���� �ʱ�ȭ
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
	if (ptr) //null�� ���� ������
	{
		//���� ������ ���� Ʈ������ ��Ʈ�� ������ �ݺ�
		//print�� ��ġ�� ��ȸ ����� ������ �� ����
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
	printf("8.1.1. Ʈ�� ���� (A = make_tree_by_code())\n");
	NodePointer A = make_tree_by_code();
	
	printf("8.1.2.Ʈ�� ��ȸ(A)\n");
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
