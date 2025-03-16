/*
�ڷᱸ�� �׷���
���⼺ ����. ����ġ ����
��� �������� ����
*/

#include <stdio.h>
#include <stdlib.h>
#define INT_MAX 99999
#define FALSE 0
#define TRUE 1

int** create_matrix(int n)
//���� ä������ ���� nxn �⺻ ��� ����
//main���� �� ä��
{
    int** G = (int**)malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++) {
        G[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
            if(i == j)
                G[i][j] = 0; //���γ����� �Ÿ� 0
            else
                G[i][j] = INT_MAX; //�������� ���� 99999
    }

    return G;
}

void print_matrix(int** G, int n)
//nxn ��� ���
{
    printf("      ");
    for (int j = 0; j < n; j++) printf("  [ %d]", j);
    printf("\n");

    for (int i = 0; i < n; i++)
    {
        printf("  [ %d]", i);
        for (int j = 0; j < n; j++) printf(" %5d", G[i][j]);
        printf("\n");
    }
}

void print_distance(int* distance, int n)
//�� ��忡�� �ִ� ��� ����� distance �迭 ���
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", distance[i]);
    }
    printf("\n");
}


void shortestPath(int v, int** G, int* distance, int n, int* found)
//�� ��忡�� �� �� �ִ� ��� ������ �ִ� ��� ���ϱ� �Լ�
{
    int i, u, w;
    for (i = 0; i < n; i++) {
        found[i] = FALSE;
        distance[i] = G[v][i];
    }
    
    found[v] = TRUE;
    distance[v] = 0;
    for (i = 0;i < n - 2;i++) {
        u = choose(distance, n, found); //found�� False�� �� �߿� �ּҰ� ����
        found[u] = TRUE;
        for (w = 0;w < n;w++)
            if (!found[w])
                if (distance[u] + G[u][w] < distance[w])
                    distance[w] = distance[u] + G[u][w];
    }

}

int choose(int* distance, int n, int* found)
//���� �湮���� ���� ������ �߿��� ���� �������κ����� �Ÿ��� ���� ª�� ������ ����
{
    int i, min, minpos;

    min = INT_MAX;
    minpos = -1;
    for (i = 0;i < n;i++)
        if (distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    return minpos;

}

void allCosts(int** G, int** matrix_distance, int n)
//��� ��ο��� �� �� �ִ� ��� ������ �ִ� ���
{
    int i, j, k;

    //matrix_distance ���Ϸ����ϴ� ��İ����� �ʱ�ȭ
    for (i = 0;i < n;i++)
        for (j = 0;j < n;j++)
            matrix_distance[i][j] = G[i][j];

    for (k = 0;k < n;k++)
        for (i = 0;i < n;i++)
            for (j = 0;j < n;j++)
                if (matrix_distance[i][k] + matrix_distance[k][j] < matrix_distance[i][j])
                    matrix_distance[i][j] = matrix_distance[i][k] + matrix_distance[k][j];
}

int main()
{
    while (1)
    {
        int n, from, to, w, v;
        int** G, ** matrix_distance;

        printf("11.1. ���� ��� ������ ���⼺ �׷��� ����\n");
        printf("  ��� �� (n) : ");
        scanf_s("%d", &n);
        if (n < 0) break;
        G = create_matrix(n);
        while (1)
        {
            printf("  ���� ���� (from to weight) : ");
            scanf_s("%d %d %d", &from, &to, &w);
            if (from < 0 || to < 0) break;
            G[from][to] = w;
        }
        printf("\n  ���� ����� �̿��� �׷����� ���� :\n");
        print_matrix(G, n);

        int* distance = (int*)malloc(n * sizeof(int)); //���� �������κ����� �ִ� ��� �Ÿ�
        int* found = (int*)malloc(n * sizeof(int));  //�湮�� ���� ǥ��

        printf("\n11.2. �ִ� ��� (���� �����)\n");
        while (1)
        {
            printf("  ���� ��� (v) : ");
            scanf_s("%d", &v);
            if (v < 0) break;
            shortestPath(v, G, distance, n, found);
            printf("  Distance : ");
            print_distance(distance, n);
        }

        printf("\n11.3. �ִ� ��� (��� ���)\n");
        printf("  All Path Distance :\n");
        matrix_distance = create_matrix(n);
        allCosts(G, matrix_distance, n);
        print_matrix(matrix_distance, n);
        printf("\n");

        free(G);
        free(distance);
        free(found);
        free(matrix_distance);
    }

    return 0;
}