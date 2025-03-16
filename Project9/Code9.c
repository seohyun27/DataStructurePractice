/*
이진 탐색 트리
왼쪽 자식은 부모보다 작은 값
오른쪽 자식은 부모보다 큰 값 저장
중복 노드 없음
연결 리스트로 구현
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define COMPARE(x, y) //정의

typedef struct node* treePointer;
typedef struct node {   	// 트리의 노드 구조
	int key; //정렬 기준
	double value; //추가 데이터
	struct node* lchild, * rchild;
} node; //struct node를 node로 대체

int count = 0;

treePointer modified_search(treePointer tree, int key)
//새 노드를 삽입하기 위한 위치를 찾아주는 함수
{
	treePointer parent = NULL;

	while (tree) {
		parent = tree;
		if (key == tree->key) //이미 존재할 때
			return NULL;
		if (key < tree->key)
			tree = tree->lchild;
		else
			tree = tree->rchild;
	}
	return parent; //NULL의 부모값 반환
}

//search 함수는 재귀함수 형태로도 구현 가능

treePointer itersearch(treePointer tree, int key)
//key를 입력받아 해당하는 위치를 리턴하는 함수
{
	while (tree) {
		count += 1;
		if (key == tree->key)
			return tree; //해당 키 값 찾으면 위치 리턴
		if (key < tree->key)
			tree = tree->lchild;
		else
			tree = tree->rchild;
	}
	return NULL;
}


void insert(treePointer* node, int key, double value)
//이진 탐색 트리에 새 노드를 추가하는 함수
//최초 생성 시 루트의 위치가 바뀜
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

treePointer make_bts(int n)
//랜덤 값을 생성해 이진 탐색 트리를 생성하는 함수
{
	treePointer A = NULL;
	int key;
	double value;

	srand(time(NULL));
	
	for(int i = 0; i < n; i++) //랜덤값 생성
	{
		key = (rand() / (0x7fff * 1.0)) * 100000000;
		value = 1.0 / key;
		printf("(%d, %f)\n", key, value); //현재 저장하는 값 출력 -> 필요하다면 삭제해도 무관
		insert(&A, key, value); //생성한 랜덤값 해당 트리에 삽입
	}

	return A;
}

void inorder(treePointer ptr)
//중위 순회 함수
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

void inorder_value(treePointer ptr)
//value값을 포함한 inorder 순회
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

int count_node(treePointer ptr)  
//노드 개수
{
	if (!ptr) return 0; //노드가 존재하지 않으면 0를 리턴
	return 1 + count_node(ptr->lchild) + count_node(ptr->rchild);
	//노드 존재하면 +1하고 모든 자식 노드에 대해 반복
}

int count_depth(treePointer ptr) 
//트리의 깊이
{
	int leftHeight, rightHeight;

	if (!ptr) return 0;
	// 왼쪽과 오른쪽 서브트리 중 더 큰 높이 + 1
	leftHeight = count_depth(ptr->lchild);
	rightHeight = count_depth(ptr->rchild);
	return 1 +
		(leftHeight > rightHeight ? leftHeight : rightHeight);
}

int count_leaf(treePointer ptr) 
//말단 노드 개수
{
	if (!ptr) return 0;
	if (!ptr->lchild && !ptr->rchild) return 1; //left, right 모두 null이면 1리턴
	return count_leaf(ptr->lchild) + count_leaf(ptr->rchild); //모든 노드에 대해 반복
}


//삭제 알고리즘 구현
//아직 테스트 안 해봄
/*
// 왼쪽 서브트리에서 가장 큰 값을 찾는 함수
treePointer find_max_node(treePointer node, treePointer* parent) {
	treePointer current = node;
	*parent = NULL;

	while (current->rchild) {
		*parent = current;
		current = current->rchild;
	}
	return current;
}

// 노드를 찾고 부모 노드의 포인터도 함께 반환하는 함수
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

// 노드 삭제 함수
void delete(treePointer* root, int key) {
	treePointer parent, node, successor, successor_parent;

	// 삭제할 노드와 그 부모를 찾음
	node = find_node(*root, key, &parent);

	if (!node) {
		printf("키 값 %d인 노드를 찾을 수 없습니다.\n", key);
		return;
	}

	// Case 1: 리프 노드인 경우
	if (!node->lchild && !node->rchild) {
		if (parent) {
			// 부모의 적절한 자식 포인터를 NULL로 설정
			if (parent->lchild == node)
				parent->lchild = NULL;
			else
				parent->rchild = NULL;
		}
		else {
			// 루트 노드인 경우
			*root = NULL;
		}
		free(node);
	}

	// Case 2: 하나의 자식만 있는 경우
	else if (!node->lchild || !node->rchild) {
		treePointer child = (node->lchild) ? node->lchild : node->rchild;

		if (parent) {
			if (parent->lchild == node)
				parent->lchild = child;
			else
				parent->rchild = child;
		}
		else {
			// 루트 노드인 경우
			*root = child;
		}
		free(node);
	}

	// Case 3: 두 개의 자식이 있는 경우
	else {
		// 왼쪽 서브트리에서 가장 큰 노드를 찾음
		successor = find_max_node(node->lchild, &successor_parent);

		// 후계자의 키와 값을 현재 노드로 복사
		node->key = successor->key;
		node->value = successor->value;

		// 후계자 노드를 삭제
		if (successor_parent) {
			// 후계자가 왼쪽 자식을 가질 수 있으므로
			successor_parent->rchild = successor->lchild;
		}
		else {
			// successor_parent가 NULL이면 node->lchild가 successor
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


	printf("9.2. 생성된 이진 검색 트리에서 key값을 활용한 검색\n");
	while (1)
	{
		count = 0;
		printf("찾고자 하는 key 값을 입력하세요 : ");
		scanf_s("%d", &key);
		if (key == -1) break;
		ptr = itersearch(A, key);
		if (ptr == NULL)
			printf("key: %d 노드가 없습니다.\n", key);
		else
			printf("count : %d, key: %d의 value: %f\n", count, ptr->key, ptr->value);
	}
	printf("\n");

	printf("9.3.n개의 노드를 가진 이진트리 생성시간 및 노드 수, 높이(깊이), 단말 노드 수 관찰\n");
	while (1)
	{
		printf("n개의 노드를 가진 이진검색 트리 생성 (n) : ");
		scanf_s("%d", &n);
		if (n == -1) break;
		printf("이진검색트리 B :\n");
		printf("(     key,    value)\n");
		start = clock();
		B = make_bts(n);
		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		printf("이진검색트리 B의 생성시간 : %f\n", duration);
		printf("이진검색트리 B의 노드 수 : %d\n", count_node(B));
		printf("이진검색트리 B의 높이(깊이) : %d\n", count_depth(B));
		printf("이진검색트리 B의 단말노드 수 : %d\n\n", count_leaf(B));
	}

	return 0;
}