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

}

void print_list(int n)
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

void reset_visited() {
	for (int i = 0; i < MAX_LIST; i++) {
		visited[i] = FALSE;
	}
}

void dfs(int v)
//재귀 함수로 스택의 역할을 대체
{
	nodePointer w;
	visited[v] = TRUE; //해당 노드 방문 표시
	printf("%5d", v);
	for (w = graph[v]; w; w = w->next)
		if (!visited[w->data]) //자식이 아직 방문하지 않았다면
			dfs(w->data); //재귀 함수 호출
}

void bfs(int v)
{
	reset_visited(); //배열 초기화

	nodePointer w;
	front = rear = -1;

	printf("%5d", v);
	visited[v] = TRUE;
	addq(v); //시작 노드로 삼을 값을 큐에 넣어두고 시작
	while (front != rear) {
		v = deleteq();
		for(w = graph[v];w;w=w->next) //아직 방문하지 않은 자식들을 저장
			if (!visited[w->data]) {
				printf("%5d", w->data);
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
	reset_visited();
	printf("  시작노드 0 : "); dfs(0); printf("\n");
	reset_visited();
	printf("  시작노드 2 : "); dfs(2); printf("\n");
	reset_visited();
	printf("  시작노드 4 : "); dfs(4); printf("\n\n");

	printf("  너비 우선 탐색 (BFS)\n");
	printf("  시작노드 1 : "); bfs(1); printf("\n");
	printf("  시작노드 3 : "); bfs(3); printf("\n");
	printf("  시작노드 5 : "); bfs(5); printf("\n\n");

	return 0;
}
