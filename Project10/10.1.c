#include <stdio.h>
#include <stdlib.h>

typedef struct node* graphsPointer;
typedef struct node {
	int data;
	struct node* next;
} node;

graphsPointer* graph = NULL;

void insert_node(int vi, int vj)
{
	graphsPointer temp = NULL, temp2 = NULL;

	temp = (graphsPointer)malloc(sizeof(*temp));
	temp->data = vj;
	if (graph[vi])
		temp->next = graph[vi];
	else
		temp->next = NULL;
	graph[vi] = temp;

	temp2 = (graphsPointer)malloc(sizeof(*temp2));
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
		graphsPointer temp = graph[i];
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
		graphsPointer temp = graph[i];
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
	graphsPointer temp = graph[max_n];
	while (temp != NULL)
	{
		printf("%d", temp->data);
		temp = temp->next;
		printf("->");
	}
	printf("end\n");
}

int main()
{
	int n, vi, vj;

	printf("10.1. 인접 리스트 형태의 무방향성 그래프 생성\n");
	printf("  노드 개수(n) : ");
	scanf_s("%d", &n);
	graph = (graphsPointer*)calloc(n, sizeof(graphsPointer));

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

	return 0;
}
