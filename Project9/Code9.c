/*
���� Ž�� Ʈ��
���� �ڽ��� �θ𺸴� ���� ��
������ �ڽ��� �θ𺸴� ū �� ����
�ߺ� ��� ����
���� ����Ʈ�� ����
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define COMPARE(x, y) //����

typedef struct node* treePointer;
typedef struct node {   	// Ʈ���� ��� ����
	int key; //���� ����
	double value; //�߰� ������
	struct node* lchild, * rchild;
} node; //struct node�� node�� ��ü

int count = 0;

treePointer modified_search(treePointer tree, int key)
//�� ��带 �����ϱ� ���� ��ġ�� ã���ִ� �Լ�
{
	treePointer parent = NULL;

	while (tree) {
		parent = tree;
		if (key == tree->key) //�̹� ������ ��
			return NULL;
		if (key < tree->key)
			tree = tree->lchild;
		else
			tree = tree->rchild;
	}
	return parent; //NULL�� �θ� ��ȯ
}

//search �Լ��� ����Լ� ���·ε� ���� ����

treePointer itersearch(treePointer tree, int key)
//key�� �Է¹޾� �ش��ϴ� ��ġ�� �����ϴ� �Լ�
{
	while (tree) {
		count += 1;
		if (key == tree->key)
			return tree; //�ش� Ű �� ã���� ��ġ ����
		if (key < tree->key)
			tree = tree->lchild;
		else
			tree = tree->rchild;
	}
	return NULL;
}


void insert(treePointer* node, int key, double value)
//���� Ž�� Ʈ���� �� ��带 �߰��ϴ� �Լ�
//���� ���� �� ��Ʈ�� ��ġ�� �ٲ�
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

treePointer make_bts(int n)
//���� ���� ������ ���� Ž�� Ʈ���� �����ϴ� �Լ�
{
	treePointer A = NULL;
	int key;
	double value;

	srand(time(NULL));
	
	for(int i = 0; i < n; i++) //������ ����
	{
		key = (rand() / (0x7fff * 1.0)) * 100000000;
		value = 1.0 / key;
		printf("(%d, %f)\n", key, value); //���� �����ϴ� �� ��� -> �ʿ��ϴٸ� �����ص� ����
		insert(&A, key, value); //������ ������ �ش� Ʈ���� ����
	}

	return A;
}

void inorder(treePointer ptr)
//���� ��ȸ �Լ�
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

void inorder_value(treePointer ptr)
//value���� ������ inorder ��ȸ
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

int count_node(treePointer ptr)  
//��� ����
{
	if (!ptr) return 0; //��尡 �������� ������ 0�� ����
	return 1 + count_node(ptr->lchild) + count_node(ptr->rchild);
	//��� �����ϸ� +1�ϰ� ��� �ڽ� ��忡 ���� �ݺ�
}

int count_depth(treePointer ptr) 
//Ʈ���� ����
{
	int leftHeight, rightHeight;

	if (!ptr) return 0;
	// ���ʰ� ������ ����Ʈ�� �� �� ū ���� + 1
	leftHeight = count_depth(ptr->lchild);
	rightHeight = count_depth(ptr->rchild);
	return 1 +
		(leftHeight > rightHeight ? leftHeight : rightHeight);
}

int count_leaf(treePointer ptr) 
//���� ��� ����
{
	if (!ptr) return 0;
	if (!ptr->lchild && !ptr->rchild) return 1; //left, right ��� null�̸� 1����
	return count_leaf(ptr->lchild) + count_leaf(ptr->rchild); //��� ��忡 ���� �ݺ�
}


//���� �˰��� ����
//���� �׽�Ʈ �� �غ�
/*
// ���� ����Ʈ������ ���� ū ���� ã�� �Լ�
treePointer find_max_node(treePointer node, treePointer* parent) {
	treePointer current = node;
	*parent = NULL;

	while (current->rchild) {
		*parent = current;
		current = current->rchild;
	}
	return current;
}

// ��带 ã�� �θ� ����� �����͵� �Բ� ��ȯ�ϴ� �Լ�
treePointer find_node(treePointer root, int key, treePointer* parent) {
	treePointer current = root;
	*parent = NULL;

	while (current && current->key != key) {
		*parent = current;
		if (key < current->key)
			current = current->lchild;
		else
			current = current->rchild;
	}
	return current;
}

// ��� ���� �Լ�
void delete(treePointer* root, int key) {
	treePointer parent, node, successor, successor_parent;

	// ������ ���� �� �θ� ã��
	node = find_node(*root, key, &parent);

	if (!node) {
		printf("Ű �� %d�� ��带 ã�� �� �����ϴ�.\n", key);
		return;
	}

	// Case 1: ���� ����� ���
	if (!node->lchild && !node->rchild) {
		if (parent) {
			// �θ��� ������ �ڽ� �����͸� NULL�� ����
			if (parent->lchild == node)
				parent->lchild = NULL;
			else
				parent->rchild = NULL;
		}
		else {
			// ��Ʈ ����� ���
			*root = NULL;
		}
		free(node);
	}

	// Case 2: �ϳ��� �ڽĸ� �ִ� ���
	else if (!node->lchild || !node->rchild) {
		treePointer child = (node->lchild) ? node->lchild : node->rchild;

		if (parent) {
			if (parent->lchild == node)
				parent->lchild = child;
			else
				parent->rchild = child;
		}
		else {
			// ��Ʈ ����� ���
			*root = child;
		}
		free(node);
	}

	// Case 3: �� ���� �ڽ��� �ִ� ���
	else {
		// ���� ����Ʈ������ ���� ū ��带 ã��
		successor = find_max_node(node->lchild, &successor_parent);

		// �İ����� Ű�� ���� ���� ���� ����
		node->key = successor->key;
		node->value = successor->value;

		// �İ��� ��带 ����
		if (successor_parent) {
			// �İ��ڰ� ���� �ڽ��� ���� �� �����Ƿ�
			successor_parent->rchild = successor->lchild;
		}
		else {
			// successor_parent�� NULL�̸� node->lchild�� successor
			node->lchild = successor->lchild;
		}
		free(successor);
	}
}
*/



int main()
{
	treePointer A = NULL, B = NULL, ptr = NULL;
	int key, n;
	double duration;
	clock_t start;

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


	printf("9.2. ������ ���� �˻� Ʈ������ key���� Ȱ���� �˻�\n");
	while (1)
	{
		count = 0;
		printf("ã���� �ϴ� key ���� �Է��ϼ��� : ");
		scanf_s("%d", &key);
		if (key == -1) break;
		ptr = itersearch(A, key);
		if (ptr == NULL)
			printf("key: %d ��尡 �����ϴ�.\n", key);
		else
			printf("count : %d, key: %d�� value: %f\n", count, ptr->key, ptr->value);
	}
	printf("\n");

	printf("9.3.n���� ��带 ���� ����Ʈ�� �����ð� �� ��� ��, ����(����), �ܸ� ��� �� ����\n");
	while (1)
	{
		printf("n���� ��带 ���� �����˻� Ʈ�� ���� (n) : ");
		scanf_s("%d", &n);
		if (n == -1) break;
		printf("�����˻�Ʈ�� B :\n");
		printf("(     key,    value)\n");
		start = clock();
		B = make_bts(n);
		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		printf("�����˻�Ʈ�� B�� �����ð� : %f\n", duration);
		printf("�����˻�Ʈ�� B�� ��� �� : %d\n", count_node(B));
		printf("�����˻�Ʈ�� B�� ����(����) : %d\n", count_depth(B));
		printf("�����˻�Ʈ�� B�� �ܸ���� �� : %d\n\n", count_leaf(B));
	}

	return 0;
}