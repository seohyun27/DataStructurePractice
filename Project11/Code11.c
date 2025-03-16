/*
자료구조 그래프
방향성 가짐. 가중치 있음
행렬 형식으로 구현
*/

#include <stdio.h>
#include <stdlib.h>
#define INT_MAX 99999
#define FALSE 0
#define TRUE 1

int** create_matrix(int n)
//값이 채워지지 않은 nxn 기본 행렬 생성
//main에서 값 채움
{
    int** G = (int**)malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++) {
        G[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
            if(i == j)
                G[i][j] = 0; //본인끼리는 거리 0
            else
                G[i][j] = INT_MAX; //나머지는 전부 99999
    }

    return G;
}

void print_matrix(int** G, int n)
//nxn 행렬 출력
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
//한 노드에서 최단 경로 결과인 distance 배열 출력
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", distance[i]);
    }
    printf("\n");
}


void shortestPath(int v, int** G, int* distance, int n, int* found)
//한 노드에서 갈 수 있는 모든 노드들의 최단 경로 구하기 함수
{
    int i, u, w;
    for (i = 0; i < n; i++) {
        found[i] = FALSE;
        distance[i] = G[v][i];
    }
    
    found[v] = TRUE;
    distance[v] = 0;
    for (i = 0;i < n - 2;i++) {
        u = choose(distance, n, found); //found가 False인 것 중에 최소값 리턴
        found[u] = TRUE;
        for (w = 0;w < n;w++)
            if (!found[w])
                if (distance[u] + G[u][w] < distance[w])
                    distance[w] = distance[u] + G[u][w];
    }

}

int choose(int* distance, int n, int* found)
//아직 방문하지 않은 정점들 중에서 시작 정점으로부터의 거리가 가장 짧은 정점을 선택
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
//모든 경로에서 갈 수 있는 모든 노드들의 최단 경로
{
    int i, j, k;

    //matrix_distance 구하려고하는 행렬값으로 초기화
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

        printf("11.1. 인접 행렬 형태의 방향성 그래프 생성\n");
        printf("  노드 수 (n) : ");
        scanf_s("%d", &n);
        if (n < 0) break;
        G = create_matrix(n);
        while (1)
        {
            printf("  에지 정보 (from to weight) : ");
            scanf_s("%d %d %d", &from, &to, &w);
            if (from < 0 || to < 0) break;
            G[from][to] = w;
        }
        printf("\n  인접 행렬을 이용한 그래프의 구성 :\n");
        print_matrix(G, n);

        int* distance = (int*)malloc(n * sizeof(int)); //시작 정점으로부터의 최단 경로 거리
        int* found = (int*)malloc(n * sizeof(int));  //방문한 정점 표시

        printf("\n11.2. 최단 경로 (단일 출발점)\n");
        while (1)
        {
            printf("  시작 노드 (v) : ");
            scanf_s("%d", &v);
            if (v < 0) break;
            shortestPath(v, G, distance, n, found);
            printf("  Distance : ");
            print_distance(distance, n);
        }

        printf("\n11.3. 최단 경로 (모든 경로)\n");
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