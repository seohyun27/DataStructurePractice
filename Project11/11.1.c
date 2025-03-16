#include <stdio.h>
#include <stdlib.h>
#define MAX_INT 99999


int** create_matrix(int n) {
    int** G = (int**)malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++) {
        G[i] = (int*)malloc(n * sizeof(int));

        for (int j = 0; j < n; j++) G[i][j] = MAX_INT;
    }
    for (int i = 0; i < n; i++) G[i][i] = 0;

    return G;
}

void print_matrix(int** G, int n) {
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

int main()
{
	int n, from, to, w;
    int** G;

	printf("11.1. 인접 행렬 형태의 방향성 그래프 생성\n");
	printf("  노드 수 (n) : ");
	scanf_s("%d", &n);
    G = create_matrix(n);
    while (1)
    {
        printf("  에지 정보 (from to weight) : ");
        scanf_s("%d %d %d", &from, &to, &w);
        if (from < 0) break;
        G[from][to] = w;
    }
    printf("\n  인접 행렬을 이용한 그래프의 구성 :\n");
    print_matrix(G, n);

	return 0;
}