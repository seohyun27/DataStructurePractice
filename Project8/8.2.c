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

NodePointer copy(NodePointer origin)
{
	NodePointer temp;

	if (origin) {
		NodePointer temp = (NodePointer)malloc(sizeof(struct node));
		temp->lchild = copy(origin->lchild); //���� ������ link�� �� ����
		temp->rchild = copy(origin->rchild); //������ ������ link�� �� ����
		temp->data = origin->data; //���� ��Ͱ� �� ������ �����͸� ���� �� ����
		return temp;
	}
	return NULL;
}

int equal(NodePointer fisrt, NodePointer second)
{
	//only return���θ� �̷���� �Լ�
	return((!fisrt && !second) || // 1. fisrt�� second�� ��� �� �� �������� �ʰų�
		// 2. �� �� ��� �����ϸ鼭 ��� ���� ���� ����
		(fisrt && second && (fisrt->data == second->data) &&
			//���ʰ� �����ʿ����� �����ϰ� ���� �� ��
			equal(fisrt->lchild, second->lchild) &&
			equal(fisrt->rchild, second->rchild)));
}

NodePointer swap(NodePointer origin)
{
	NodePointer temp;

	if (origin) {
		NodePointer temp = (NodePointer)malloc(sizeof(struct node));
		temp->rchild = swap(origin->lchild); //������ ������ link�� �� �������� ����
		temp->lchild = swap(origin->rchild); //���� ������ link�� �� ���������� ����
		temp->data = origin->data; //���� ��Ͱ� �� ������ ������ ���
		return temp;
	}
	return NULL;
}

int main(void)
{
	NodePointer A, B, C;
	int result;

	printf("8.1.1. Ʈ�� ���� (A = make_tree_by_code())\n");
	A = make_tree_by_code();
	printf("8.1.2.Ʈ�� ��ȸ(A)\n");
	printf("inorder(A) : ");
	inorder(A);
	printf("\n");
	printf("preorder(A) : ");
	preorder(A);
	printf("\n");
	printf("postorder(A) : ");
	postorder(A);
	printf("\n\n");

	printf("8.2.1.Ʈ�� ����(B = copy(A))\n");
	B = copy(A);
	printf("8.2.2.Ʈ�� ��ȸ (B)\n");
	printf("inorder(B) : ");
	inorder(B);
	printf("\n");
	printf("preorder(B) : ");
	preorder(B);
	printf("\n");
	printf("postorder(B) : ");
	postorder(B);
	printf("\n\n");

	printf("8.2.3.Ʈ�� ������ �˻�(equal(A, B)\n");
	result = equal(A, B);
	printf("equal(A, B) : ");
	if (result)
		printf("TRUE\n\n");
	else
		printf("FALSE\n\n");

	printf("8.2.4. Ʈ�� swap (C = swap(A))\n");
	C = swap(A);
	printf("8.2.5. Ʈ�� ��ȸ (C)\n");
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
