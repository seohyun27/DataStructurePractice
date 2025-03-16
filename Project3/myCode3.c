#include <stdio.h>
#include <stdlib.h>

#define COMPARE(x,y) ( ((x)<(y)) ? -1 : ((x)==(y)) ? 0 : 1 )

typedef struct polynomial { //다항식 구조체
	float coef; //계수
	int expon; //지수
}polynomial;
//struct 뒤에 polynomial을 명시하면 struct polynomial을 부를 수 있
//명시하는 것을 추천

//모든 다항식에 현재 내 위치와 D 사이즈를 표현하는 변수가 하나씩 필요함
int k; //현재 내 위치
int max_D; //D 사이즈

polynomial* A;
polynomial* B;
polynomial* D;
polynomial* Ci;
int size; //배열의 크기
int count; //인덱스 값
int Ci_size;
int Ci_count;
int old_count;

void attach(float coef, int expon, polynomial* D);
polynomial* padd(polynomial* A, polynomial* B, polynomial* D);
polynomial* single_mul(polynomial Ai, polynomial* B, polynomial* Ci);
polynomial* pmul(polynomial* A, polynomial* B, polynomial* D);

void main(void)
{
	while (1)
	{
		A = (polynomial*)malloc(sizeof(polynomial) * 10); //초기 할당
		B = (polynomial*)malloc(sizeof(polynomial) * 10);
		D = (polynomial*)malloc(sizeof(polynomial) * 10);

		size = 10;
		count = 0;
		Ci_size = 10;
		Ci_count = 0;

		int A_size = 10;
		int A_count = 0;
		int B_size = 10;
		int B_count = 0;

		printf("3.1. 다항식 생성\n");
		// 다항식 A(x) 입력
		while (1)
		{
			float coef;
			int expon;

			printf("A(x)의 항을 입력하세요. (coef expon) : ");
			scanf_s("%f %d", &coef, &expon);
			if (A_count >= A_size - 1) { //배열에 자리가 남았는지 확인
				A_size += 10;
				A = (polynomial*)realloc(A, A_size * sizeof(polynomial));
			}
			A[A_count].coef = coef;
			A[A_count].expon = expon;
			A_count++;

			if (expon == -1) {
				break;
			}
		}
		printf("\n");

		//다항식 A(x) 출력
		printf("다항식 A(x)\n");
		printf("    coef      expon\n");
		for (int i = 0; i < A_count - 1; i++) { //-1이 담긴 마지막 항은 생략하고 출력
			printf("    %.2f\t%d\n", A[i].coef, A[i].expon);
		}
		printf("\n");

		// 다항식 B(x) 입력
		while (1)
		{
			float coef;
			int expon;

			printf("B(x)의 항을 입력하세요. (coef expon) : ");
			scanf_s("%f %d", &coef, &expon);
			if (B_count >= B_size - 1) {
				B_size += 10;
				B = (polynomial*)realloc(B, B_size * sizeof(polynomial));
			}
			B[B_count].coef = coef;
			B[B_count].expon = expon;
			B_count++;

			if (expon == -1) {
				break;
			}
		}
		printf("\n");

		//다항식 B(x) 출력
		printf("다항식 B(x)\n");
		printf("    coef      expon\n");
		for (int i = 0; i < B_count - 1; i++) {
			printf("    %.2f\t%d\n", B[i].coef, B[i].expon);
		}
		printf("\n");

		// 다항식의 덧셈 결과 출력
		printf("3.2 다항식 덧셈\n");
		D = padd(A, B, D);
		printf("다항식 덧셈 결과 : D(x)\n");
		printf("    coef      expon\n");
		for (int i = 0; i < count; i++) {
			printf("    %.2f\t%d\n", D[i].coef, D[i].expon);
		}
		printf("\n");
		free(D);

		// 다항식의 곱셈 결과 출력
		count = 0;
		size = 10;
		D = (polynomial*)malloc(sizeof(polynomial) * 10);
		printf("3.3 다항식 곱셈\n");
		D = pmul(A, B, D);

		free(A);
		free(B);
		free(D);
	}
}


void attach(float coef, int expon, polynomial* D)
{
	if (count >= size - 1) { //배열에 자리가 남았는지 확인
		size += 10;
		D = (polynomial*)realloc(D, size * sizeof(polynomial));
	}
	D[count].coef = coef;
	D[count].expon = expon;
	count++;
}

polynomial* padd(polynomial* A, polynomial* B, polynomial* D)
{
	int i = 0;
	int j = 0;
	float coef; //D에게 attach할 항의 계수를 넣어두는 변수

	while (A[i].expon != -1 && B[j].expon != -1) //다항식 A, B중에 하나의 항이 끝날 때까지
	{
		switch (COMPARE(A[i].expon, B[j].expon)) //두 항의 지수 비교
		{
		case -1: //B 지수가 클 때
			attach(B[j].coef, B[j].expon, D); //B항을 그대로 어테치
			j++;
			break;
		case 0:
			coef = A[i].coef + B[j].coef; //A B 계수 더하기
			if (coef) //계수가 0이 아니라면
				attach(coef, A[i].expon, D);
			i++;
			j++;
			break;
		case 1:
			attach(A[i].coef, A[i].expon, D); //A항을 그대로 어테치
			i++;
		}
	}
	//다항식 A, B중에 하나의 항이 끝났을 때
	//남은 다항식의 항을 모두 어테치 해줌
	for (; A[i].expon != -1; i++) //A가 남았을 때
		attach(A[i].coef, A[i].expon, D);
	for (; B[j].expon != -1; j++)//B가 남았을 때
		attach(B[j].coef, B[j].expon, D);

	return D; //배열 D 반환
}

polynomial* single_mul(polynomial Ai, polynomial* B, polynomial* Ci)
//A의 항 하나(Ai)와 B의 다항식을 곱하는 함수
{
	Ci_count = 0;
	Ci_size = 10;

	for (int i = 0; B[i].expon != -1; i++)
	{
		if (Ci_count >= Ci_size - 1) { //Ci 배열에 자리가 남았는지 확인
			Ci_size += 10;
			Ci = (polynomial*)realloc(Ci, Ci_size * sizeof(polynomial));
		}
		Ci[Ci_count].coef = Ai.coef * B[i].coef;
		Ci[Ci_count].expon = Ai.expon + B[i].expon;
		Ci_count++;
	}
	Ci[Ci_count].coef = -1;
	Ci[Ci_count].expon = -1;

	return Ci;
}

polynomial* pmul(polynomial* A, polynomial* B, polynomial* D)
{
	polynomial* temp = (polynomial*)malloc(sizeof(polynomial) * size); //temp 배열 생성

	//첫 번째 곱셈 수행
	temp = single_mul(A[0], B, temp);
	count = 0;  // count 초기화

	//temp의 결과를 D에 복사
	for (int i = 0; temp[i].expon != -1; i++) {
		attach(temp[i].coef, temp[i].expon, D);
	}
	D[count].coef = -1;
	D[count].expon = -1;

	printf("singul_mul - C1(x)\n");
	printf("    coef      expon\n");
	for (int j = 0; j < count; j++) {
		printf("    %.2f\t%d\n", D[j].coef, D[j].expon);
	}
	printf("\n");

	for (int i = 1; A[i].expon != -1; i++)
	{
		polynomial* Ci = (polynomial*)malloc(sizeof(polynomial) * size);

		Ci = single_mul(A[i], B, Ci);

		if (old_count + Ci_count > size) {
			size += 10;
			D = (polynomial*)realloc(D, size * sizeof(polynomial));
			temp = (polynomial*)realloc(temp, size * sizeof(polynomial));
		}

		printf("singul_mul - C%d(x)\n", (i + 1));
		printf("    coef      expon\n");
		for (int j = 0; Ci[j].expon != -1; j++) {
			printf("    %.2f\t%d\n", Ci[j].coef, Ci[j].expon);
		}
		printf("\n");

		//D의 현재 내용을 temp에 복사
		int valid_count = 0;
		for (int j = 0; j < count && D[j].expon != -1; j++) {
			temp[j].coef = D[j].coef;
			temp[j].expon = D[j].expon;
			valid_count++;
		}
		temp[valid_count].coef = -1;
		temp[valid_count].expon = -1;

		//count의 값을 old_count에 담아두기
		int old_count = count;
		count = 0;

		// temp와 Ci를 더해서 D에 저장
		D = padd(temp, Ci, D);
		D[count].coef = -1;
		D[count].expon = -1;

		free(Ci);
	}

	printf("다항식 곱셈 결과 : D(x)\n");
	printf("    coef      expon\n");
	for (int j = 0; j < count - 1; j++) {
		printf("    %.2f\t%d\n", D[j].coef, D[j].expon);
	}
	printf("\n");


	free(temp);
	return D;
}
