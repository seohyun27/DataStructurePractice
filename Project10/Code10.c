/*
자료구조 [그래프]의 기본 연산
무방향성 그래프. 가중치 없음
연결 리스트로 구현
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_LIST 20
#define ERROR_KEY -999
#define FALSE 0
#define TRUE 1

typedef struct node* nodePointer;
typedef struct node {
	int data;
	struct node* next;
} node;

nodePointer* graph = NULL; //그래프
short int visited[MAX_LIST]; //방문한 노드를 검사

int queue[MAX_LIST]; //큐
int front = -1;
int rear = -1;

void addq(int data)
{
	if (rear >= MAX_LIST - 1) {
		printf("Queue is full.\n");
		return;
	}
	queue[++rear] = data;
}

int deleteq()
{
	if (front == rear) {
		printf("Queue is empty.\n");
		return ERROR_KEY;
	}
	return queue[++front];
}

void insert_node(int vi, int vj)
//노드를 생성해서 그래프에 추가하는 함수
{
	nodePointer temp = NULL, temp2 = NULL;

	temp = (nodePointer)malloc(sizeof(*temp));
	temp->data = vj;
	if (graph[vi])
		temp->next = graph[vi];
	else
		temp->next = NULL;
	graph[vi] = temp;

	temp2 = (nodePointer)malloc(sizeof(*temp2));
	temp2->data = vi;
	if (graph[vj])
		temp2->next = graph[vj];
	else
		temp2->next = NULL;
	graph[vj] = temp2;

	/*
	무방향성 그래프이므로 vi, vj에서 2번 반복
	새로운 노드(temp)를 생성
	temp의 data에 vj 저장
	temp를 graph[vi]의 맨 앞에 연결
	*/
}

void print_list(int n)
//그래프 출력
{
	for (int i = 0;i < n;i++)
	{
		printf("  [%d] : ", i);
		nodePointer temp = graph[i];
		while (temp != NULL)
		{
			printf("%d", temp->data);
			temp = temp->next;
			printf("->");
		}
		printf("end\n");
	}
}

void max_degree(int n)
//가장 많은 연결이 달린 노드를 찾고, 그 노드의 정보를 출력하는 함수
{
	int count = 0, max_count = 0;
	int max_n = 0;

	for (int i = 0;i < n;i++)
	{
		nodePointer temp = graph[i];
		for (;temp != NULL;temp = temp->next)
			count++;
		if (count > max_count)
		{
			max_count = count;
			max_n = i;
		}
		count = 0;
	}
	printf("  degree가 가장 큰 노드와 degree 값 : 노드 %d, degree %d\n", max_n, max_count);

	//해당 노드 출력
	printf("  노드 %d와 연결된 노드들 : ", max_n);
	nodePointer temp = graph[max_n];
	while (temp != NULL)
	{
		printf("%d", temp->data);
		temp = temp->next;
		printf("->");
	}
	printf("end\n");
}

void reset_visited()
//방문 여부를 표시하는 visited 배열 리셋
{

	for (int i = 0; i < MAX_LIST; i++) {
		visited[i] = FALSE;
	}
}

void dfs(int v)
//깊이 우선 탐색
//재귀 함수로 스택의 역할을 대체
{
	nodePointer w;
	visited[v] = TRUE; //해당 노드 방문 표시
	printf("%5d", v);
	for (w = graph[v]; w; w = w->next)
		if (!visited[w->data]) //자식이 아직 방문하지 않았다면
			dfs(w->data); //자식에서 다시 재귀 함수 호출
	//가장 마지막에 찾은 애부터 재귀 함수 나오며 순차적으로 처리 -> 스택
}

void bfs(int v)
//넓이 우선 탐색
//큐 하나를 생성해서 사용
{
	reset_visited(); //배열 초기화

	nodePointer w;
	front = rear = -1;

	printf("%5d", v);
	visited[v] = TRUE;
	addq(v); //시작 노드로 삼을 값을 큐에 넣어두고 시작
	while (front != rear) {
		v = deleteq();
		for (w = graph[v];w;w = w->next) //아직 방문하지 않은 자식들을 저장
			if (!visited[w->data]) {
				printf("%5d", w->data);
				addq(w->data);
				visited[w->data] = TRUE;
			}
	}
}

void dfs_spanning_tree(int v)
//깊이 우선 탐색을 이용한 신장 트리
{
	nodePointer w;
	visited[v] = TRUE; //해당 노드 방문 표시

	for (w = graph[v]; w; w = w->next)
		if (!visited[w->data]) //자식이 아직 방문하지 않았다면
		{
			//그래프의 인접 노드
			//부모 노드에 따른 자식 노드 출력
			printf("  (%d, %d)", v, w->data);
			dfs_spanning_tree(w->data);
		}
}

void bfs_spanning_tree(int v)
//넓이 우선 탐색을 이용한 신장 트리
//결과가 제대로 출력되는 건지 아직 확인 못 해봄 -> 거의 맞는 듯
{
	front = rear = -1;
	nodePointer w;
	visited[v] = TRUE;
	addq(v);
	while (front != rear)
	{
		v = deleteq();
		for(w = graph[v]; w; w = w->next)
			if (!visited[w->data]) //자식이 아직 방문하지 않았다면
			{
				//그래프의 인접 노드
				//부모 노드에 따른 자식 노드 출력
				printf("  (%d, %d)", v, w->data);
				addq(w->data);
				visited[w->data] = TRUE;
			}
	}

}

int main()
{
	int n, vi, vj;

	printf("10.1. 인접 리스트 형태의 무방향성 그래프 생성\n");
	printf("  노드 개수(n) : ");
	scanf_s("%d", &n);
	graph = (nodePointer*)calloc(n, sizeof(nodePointer)); 
	//n개의 노드를 가진 배열? 생성

	while (1)
	{
		printf("  에지 정보(vi vj) : ");
		scanf_s("%d %d", &vi, &vj);
		if (vi < 0) break;
		insert_node(vi, vj);
	}
	printf("\n");

	printf("  인접 리스트를 이용하여 구성한 그래프\n");
	print_list(n);
	printf("\n");

	max_degree(n);
	printf("\n");

	printf("10.2. 탐색 알고리즘(DFS, BFS)\n");
	printf("  깊이 우선 탐색 (DFS)\n");
	reset_visited(); //visited 배열 FALSE로 초기화
	printf("  시작노드 0 : "); dfs(0); printf("\n");
	reset_visited();
	printf("  시작노드 2 : "); dfs(2); printf("\n");
	reset_visited();
	printf("  시작노드 4 : "); dfs(4); printf("\n\n");

	printf("  너비 우선 탐색 (BFS)\n");
	printf("  시작노드 1 : "); bfs(1); printf("\n");
	printf("  시작노드 3 : "); bfs(3); printf("\n");
	printf("  시작노드 5 : "); bfs(5); printf("\n\n");

	printf("10.3. 신장트리 알고리즘(DFS, BFS 기반)\n");
	printf("  DFS 신장트리\n");
	reset_visited();
	printf("  시작노드 0 : "); dfs_spanning_tree(0); printf("\n");
	reset_visited();
	printf("  시작노드 2 : "); dfs_spanning_tree(2); printf("\n");
	reset_visited();
	printf("  시작노드 4 : "); dfs_spanning_tree(4); printf("\n\n");
	
	printf("  BFS 신장트리\n");
	reset_visited();
	printf("  시작노드 0 : "); bfs_spanning_tree(0); printf("\n");
	reset_visited();
	printf("  시작노드 2 : "); bfs_spanning_tree(2); printf("\n");
	reset_visited();
	printf("  시작노드 4 : "); bfs_spanning_tree(4); printf("\n\n");

	return 0;
}
