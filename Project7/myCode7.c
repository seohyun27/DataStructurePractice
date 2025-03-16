#include <stdio.h>
#include <stdlib.h>
#define COMPARE(x,y) ( ((x)<(y)) ? -1 : ((x)==(y)) ? 0 : 1 )
#define ERROR_KEY -999

struct poly
{
	float coef; //계수
	int expon; //지수
	struct poly* link;
};
typedef struct poly* polyPointer; //구조체 node의 포인터를 nodePointer로 정의

polyPointer avail; //가용 공간 리스트의 first

polyPointer getNode(void)
//Node 불러오기
{
	polyPointer node;
	if (avail) { //avail이 null이 아니라면
		node = avail; //node에 avail값 담아두기
		avail = avail->link; //avail 한 칸 뒤로 이동
	}
	else
		node = (polyPointer)malloc(sizeof(*node));
	return node;
}

void retNode(polyPointer node)
//Node 반환하기
{
	node->link = avail; //node->link에 avail값을 넣기
	avail = node; //avail은 node를 가리키도록
}

void cerease(polyPointer* ptr) //주소의 주소를 입력
//다항식을 통째로 avail에 반환하기
{
	polyPointer temp;
	if (*ptr) {
		temp = (*ptr)->link; //*ptr의 시작점을 temp에 담아둠
		(*ptr)->link = avail; //avail을 *ptr에 이어줌
		avail = temp; //temp에 담아둔 주소에 avail 옮기기
		*ptr = NULL; //*ptr을 베워줌
	}
}

polyPointer creat_polynomial() //다항씩 쌍을 입력받아 큐에 저장
{
	polyPointer temp, first, rear;
	float coef;
	int expon;

	first = getNode();
	first->coef = -1;
	first->expon = -1;
	rear = first;

	while (1)
	{
		printf("다항식의 항을 입력하세요. (coef expon) : ");
		scanf_s("%f %d", &coef, &expon);
		if (expon == -1) break;

		//미리 노드를 잇고 attach하는 방법 있음

		temp = getNode();
		temp->coef = coef;
		temp->expon = expon;
		temp->link = NULL;

		if (first->link)
			rear->link = temp;
		else
			first->link = temp;
		rear = temp;
	}
	rear->link = first; //헤더와 끝 노드 이어주기

	return first;
}

void attach(float coef, int expon, polyPointer* ptr) //ptr = rear
{
	polyPointer temp;
	temp = getNode();

	temp->coef = coef;
	temp->expon = expon;
	(*ptr)->link = temp; //rear이용해서 뒤로 이어주기
	*ptr = temp;
}

void print_polynomial(polyPointer ptr)
{
	ptr = ptr->link;
	printf("    coef   expon\n");
	for (;ptr->expon != -1;ptr = ptr->link)
		printf("%8.2f %8d\n", ptr->coef, ptr->expon);
}

polyPointer cpadd(polyPointer a, polyPointer b)
{
	polyPointer startA, c, lastC;
	int sum, done = 0;
	startA = a; //a의 시작노드 기록

	a = a->link;
	b = b->link; //더미노드 건너띄기

	c = getNode();
	c->expon = -1;
	lastC = c; //c의 더미노드

	do {
		switch (COMPARE(a->expon, b->expon))
		{
		case -1:
			attach(b->coef, b->expon, &lastC);
			b = b->link;
			break;
		case 0:
			if (startA == a) done = 1;
			else {
				sum = a->coef + b->coef;
				if (sum)
					attach(sum, a->expon, &lastC);
				a = a->link;
				b = b->link;
			}
			break;
		case 1:
			attach(a->coef, a->expon, &lastC);
			a = a->link;
			break;
		}
	} while (!done);
	lastC->link = c; //last와 첫 노드 이어주기
	return c;
}

polyPointer single_mul(struct poly Ai, polyPointer B)
//A의 항 하나와 B의 다항식을 곱하는 함수
{
	float coef;
	int expon;
	polyPointer startB, X, lastX;
	startB = B;
	B = B->link; //더미노드 건너띄기

	X = getNode();
	X->expon = -1;
	lastX = X; //x의 더미노드

	while (B != startB) {
		coef = Ai.coef * B->coef;
		expon = Ai.expon + B->expon;
		attach(coef, expon, &lastX);
		B = B->link;
	}

	lastX->link = X; //last와 첫 노드 이어주기
	return X;
}

polyPointer cpmul(polyPointer A, polyPointer B)
//A 다항식과 B 다항식을 곱하는 함수
{
	polyPointer X, D, tempD, startA;
	startA = A;
	A = A->link; //더미노드 건너띄기

	D = getNode();
	D->expon = -1;
	D->link = D; //D 다항식을 더미노드만 있는 원형 리스트로 생성

	int i = 1;
	while (A != startA)
	{
		X = single_mul(*A, B);
		printf("singul_mul - C%d(x)\n", i);
		print_polynomial(X); //중간 결과 출력

		tempD = cpadd(D, X);
		cerease(&D); //D를 반환
		D = tempD; //NULL로 바뀐 D에 tempD를 저장

		cerease(&X);
		A = A->link; //A의 다음 항으로 이동
		i++;
	}
	return D;
}


int main(void)
{
	polyPointer A, B, C, X, D;
	A = NULL, B = NULL, C =NULL, D = NULL;
	avail = NULL;

	while (1)
	{

		printf("7.1. 다항식 생성\n");
		printf("다항식 A(x)\n");
		A = creat_polynomial();
		printf("다항식 A(x) :\n");
		print_polynomial(A);

		printf("다항식 B(x)\n");
		B = creat_polynomial();
		printf("다항식 B(x) :\n");
		print_polynomial(B);

		printf("7.2 다항식 덧셈\n");
		printf("다항식 덧셈 결과 : D(x)\n");
		C = cpadd(A, B);
		print_polynomial(C);

		printf("7.3 다항식 곱셈\n");
		D = cpmul(A, B);
		printf("다항식 곱셈 결과 : D(x)\n");
		print_polynomial(D);

		cerease(&A);
		cerease(&B);
		cerease(&C);
		cerease(&D);

		printf("\n");
	}

	return 0;
}