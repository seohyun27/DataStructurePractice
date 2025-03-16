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
	printf("  degree�� ���� ū ���� degree �� : ��� %d, degree %d\n", max_n, max_count);

	//�ش� ��� ���
	printf("  ��� %d�� ����� ���� : ", max_n);
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

	printf("10.1. ���� ����Ʈ ������ �����⼺ �׷��� ����\n");
	printf("  ��� ����(n) : ");
	scanf_s("%d", &n);
	graph = (graphsPointer*)calloc(n, sizeof(graphsPointer));

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

	return 0;
}
