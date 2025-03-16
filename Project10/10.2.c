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

nodePointer* graph = NULL; //�׷���
short int visited[MAX_LIST]; //�湮�� ��带 �˻�

int queue[MAX_LIST]; //ť
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
	printf("  degree�� ���� ū ���� degree �� : ��� %d, degree %d\n", max_n, max_count);
	
	//�ش� ��� ���
	printf("  ��� %d�� ����� ���� : ", max_n);
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
//��� �Լ��� ������ ������ ��ü
{
	nodePointer w;
	visited[v] = TRUE; //�ش� ��� �湮 ǥ��
	printf("%5d", v);
	for (w = graph[v]; w; w = w->next)
		if (!visited[w->data]) //�ڽ��� ���� �湮���� �ʾҴٸ�
			dfs(w->data); //��� �Լ� ȣ��
}

void bfs(int v)
{
	reset_visited(); //�迭 �ʱ�ȭ

	nodePointer w;
	front = rear = -1;

	printf("%5d", v);
	visited[v] = TRUE;
	addq(v); //���� ���� ���� ���� ť�� �־�ΰ� ����
	while (front != rear) {
		v = deleteq();
		for(w = graph[v];w;w=w->next) //���� �湮���� ���� �ڽĵ��� ����
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

	printf("10.1. ���� ����Ʈ ������ �����⼺ �׷��� ����\n");
	printf("  ��� ����(n) : ");
	scanf_s("%d", &n);
	graph = (nodePointer*)calloc(n, sizeof(nodePointer));

	while (1)
	{
		printf("  ���� ����(vi vj) : ");
		scanf_s("%d %d", &vi, &vj);
		if (vi < 0) break;
		insert_node(vi, vj);
	}
	printf("\n");

	printf("  ���� ����Ʈ�� �̿��Ͽ� ������ �׷���\n");
	print_list(n);
	printf("\n");

	max_degree(n);
	printf("\n");

	printf("10.2. Ž�� �˰���(DFS, BFS)\n");
	printf("  ���� �켱 Ž�� (DFS)\n");
	reset_visited();
	printf("  ���۳�� 0 : "); dfs(0); printf("\n");
	reset_visited();
	printf("  ���۳�� 2 : "); dfs(2); printf("\n");
	reset_visited();
	printf("  ���۳�� 4 : "); dfs(4); printf("\n\n");

	printf("  �ʺ� �켱 Ž�� (BFS)\n");
	printf("  ���۳�� 1 : "); bfs(1); printf("\n");
	printf("  ���۳�� 3 : "); bfs(3); printf("\n");
	printf("  ���۳�� 5 : "); bfs(5); printf("\n\n");

	return 0;
}
