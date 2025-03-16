#define _CRT_SECURE_NO_WARNINGS //scanf, strcpy에서 _s를 붙이지 않아도 오류가 나지 않도록 해주는 코드
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#define COMPARE(x,y) ( ((x)<(y)) ? -1 : ((x)==(y)) ? 0 : 1 )
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
#define MAX_TERMS 10

//struct 뒤에 구조체의 이름을 한 번 더 명시해주는 편이 좋음
//struct 뒤에 polynomial을 명시하면 struct polynomial로 사용할 수 있다
//명시하는 것을 추천
typedef struct polynomial {
	float coef; //계수
	int expon; //지수
}polynomial;

//polynomial 대신 struct polynomial로 명시하면 에러 발생을 줄일 수 있음
struct polynomial* A, * B, * D;

//모든 다항식에 현재 내 위치와 D 사이즈를 표현하는 변수가 하나씩 필요함
int k; //현재 내 위치
int max_D; //D 사이즈

void print(polynomial* A)
{
	printf("    coef   expon\n");
	for (int n = 0;A[n].expon >= 0;n++)
		printf("%8.2f %8d\n", A[n].coef, A[n].expon);
}

void attach(float coef, int expon)
{
	//어테치 전에 배열에 자리가 남아있는지 확인
	if(k==max_D) //현재 위치와 D의 사이즈가 같다면(자리X)
	{
		//D의 사이즈를 키워서 재할당
		max_D += MAX_TERMS;
		D = (polynomial*)realloc(D, sizeof(struct polynomial) * max_D);
		//재할당 시에는 할당 실패에 대한 코드를 넣어주는 편이 권장됨
	}

	D[k].coef = coef;
	D[k].expon = expon;
	k++;
}

polynomial* padd(polynomial* A, polynomial* B)
//2개의 polynomial배열을 입력받아 결과 polynomial 배열을 반환하는 함수
{
	float coef;
	int i = 0, j = 0;
	while (A[i].expon >= 0 && B[j].expon >= 0) //다항식 A, B중에 하나의 항이 끝날 때까지
	{
		switch (COMPARE(A[i].expon, B[j].expon)) //두 항의 지수 비교
		{
		case -1: //B 지수가 클 때
			attach(B[j].coef, B[j].expon); //B항을 그대로 어테치
			j++;
			break;
		case 0:
			coef = A[i].coef + B[j].coef; //A B 계수 더하기
			if (coef) //계수가 0이 아니라면
				attach(coef, A[i].expon);
			i++;
			j++;
			break;
		case 1:
			attach(A[i].coef, A[i].expon); //A항을 그대로 어테치
			i++;
		}
	}
	//다항식 A, B중에 하나의 항이 끝났을 때
	//남은 다항식의 항을 모두 어테치 해줌
	for (; A[i].expon >= 0; i++) //A가 남았을 때
		attach(A[i].coef, A[i].expon);
	for (; B[j].expon >= 0; j++)//B가 남았을 때
		attach(B[j].coef, B[j].expon);

	attach(-1, -1); //D 배열의 마지막
	return D; //배열 D 반환
}

polynomial* single_mul(polynomial Ai, polynomial* B)
//A다항식의 항 하나와 B다항식을 곱하는 함수
{
	int max_Cj = MAX_TERMS; //Cj 사이즈
	int i = 0; //Cj 현재 위치

	//결과를 저장할 배열
	polynomial* Cj = (polynomial*)malloc(sizeof(struct polynomial) * max_Cj);
	for (int j = 0; B[j].expon >= 0; j++)
	{
		if (i == max_Cj) { //Cj 현재 위치가 Cj 배열의 끝까지 도착했다면
			max_Cj += MAX_TERMS;
			Cj = (polynomial*)realloc(Cj, sizeof(struct polynomial) * max_Cj);
		}
		Cj[i].coef = Ai.coef * B[j].coef;
		Cj[i].expon = Ai.expon + B[j].expon;
		i++;
	}
	Cj[i].coef = -1;
	Cj[i].expon = -1; //경계값 표시

	return Cj;
}

polynomial* pmul(polynomial* A, polynomial* B)
//두 다항식의 곱을 구하는 함수
{
	polynomial* Cj; //single_mul(Ai, B)의 결과를 저장하는 배열
	polynomial* Ci; //Cj의 값을 누적해줄 배열

	int max_Ci = MAX_TERMS; //Ci 사이즈
	int h = 0; //Ci 현재 위치

	Ci = (polynomial*)malloc(sizeof(struct polynomial) * max_Ci);
	Ci[0].coef = -1;
	Ci[0].expon = -1;

	for (int i = 0; A[i].expon >= 0; i++) //A의 지수가 음수가 될때까지
	{
		//이곳의 Cj는 single_mul(Ai, B)에서 리턴된 Cj 배열을 그대로 넘겨받음
		//따로 배열의 크기를 정해줘야 할 필요가 없는 듯
		Cj = single_mul(A[i], B);
		printf("singul_mul - C%d\n", i + 1);
		print(Cj); //중간 결과 출력
		D = padd(Ci, Cj);
		free(Cj);
		free(Ci);

		if(A[i+1].expon >= 0) //만약 A의 다음 항이 존재한다면
		{
			Ci = D; //배열 B를 Ci안에 담아두기
			//D 배열, D현재 위치 초기화
			D = (polynomial*)malloc(sizeof(struct polynomial) * max_D);
			k = 0;
		}
	}
	return D;
}

void sortpoly(polynomial* A)
//다항식 정렬 함수
//지수를 기준으로 계수, 지수를 정렬
{
	int i, j, max;
	int temp; //지수 임시 보관 장소
	float tempf; //계수 임시 보관 장소

	for (i = 0;A[i].expon > -1;i++)
	{
		max = i;
		for (j = i + 1; A[j].expon > -1; j++)
			if (A[j].expon > A[max].expon)
				max = j;
		SWAP(A[i].expon, A[max].expon, temp);
		SWAP(A[i].coef, A[max].coef, tempf);
	}
}


int main()
{
	float coef;
	int expon;
	int n = 0, max_A;
	int m = 0, max_B;
	
	while (1)
	{
		max_A = max_B = MAX_TERMS;

		A = (polynomial*)malloc(sizeof(struct polynomial) * max_A);
		B = (polynomial*)malloc(sizeof(struct polynomial) * max_B);

		printf("3.1. 다항식 생성\n");
		// A다항식 생성
		while (1)
		{
			printf("A(x)의 항을 입력하세요. (coef expon) : ");
			scanf_s("%f %d", &coef, &expon);
			A[n].coef = coef;
			A[n].expon = expon;
			n++;

			if (expon < 0)
				break;

			//배열에 자리가 남았는지 확인
			if (n == max_A - 1) {
				max_A += MAX_TERMS;
				A = (polynomial*)realloc(A, sizeof(struct polynomial) * max_A);
			}
		}
		sortpoly(A); //배열 A를 지수 기준으로 정렬
		printf("다항식 A(x)\n");
		print(A); //배열 출력 함수


		// B다항식 생성
		while (1)
		{
			printf("B(x)의 항을 입력하세요. (coef expon) : ");
			scanf_s("%f %d", &coef, &expon);
			B[m].coef = coef;
			B[m].expon = expon;
			m++;

			if (expon < 0)
				break;

			if (m == max_B - 1)
			{
				max_B += MAX_TERMS;
				B = (polynomial*)realloc(B, sizeof(struct polynomial) * max_B);
			}
		}
		sortpoly(B);
		printf("다항식 B(x)\n");
		print(B);


		printf("3.2 다항식 덧셈\n");
		//배열 D할당
		max_D = MAX_TERMS;
		k = 0; //D의 현재 위치 초기화
		D = (polynomial*)malloc(sizeof(struct polynomial) * max_D);
		D = padd(A, B); //다항식 덧셈 함수 실행
		printf("다항식 곱셈 결과 : D(x)\n");
		print(D);
		free(D);


		printf("3.3 다항식 곱셈\n");
		//배열 D할당
		max_D = MAX_TERMS;
		k = 0;
		D = (polynomial*)malloc(sizeof(struct polynomial) * max_D);
		D = pmul(A, B); //다항식 곱셈 함수 실행
		printf("다항식 곱셈 결과 : D(x)\n");
		print(D);
	}
	return 0;
}