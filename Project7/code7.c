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
//필요없게 된 노드를 이곳으로 옮겨줌

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

void attach(float coef, int expon, polyPointer head)
//일반 attach와 다르게 rear가 필요하지 않음
{
	polyPointer temp, ptr, ptrb;
	ptrb = head;
	ptr = head->link;

	while (ptr != head) {
		if (ptr->expon < expon) break;
		ptrb = ptr; ptr = ptr->link; //1칸 씩 앞으로 이동
	}
	temp = getNode();
	temp->coef = coef;
	temp->expon = expon;
	temp->link = ptr; //노드 이어주기
	ptrb->link = temp;
}

polyPointer creat_polynomial() 
//다항씩 쌍을 입력받아 원형 리스트 큐에 저장
{
	polyPointer ptr;
	float coef;
	int expon;

	//내용이 빈 원형 연결 리스트 ptr을 만들고 시작
	ptr = getNode();
	ptr->coef = -1; ptr->expon = -1; ptr->link = ptr;

	while (1)
	{
		printf("다항식의 항을 입력하세요. (coef expon) : ");
		scanf_s("%f %d", &coef, &expon);
		if (expon == -1) break;
		attach(coef, expon, ptr);
	}
	return ptr;
}

void print_polynomial(polyPointer ptr)
//다항식 출력
{
	ptr = ptr->link;
	printf("    coef   expon\n");
	for (;ptr->expon != -1;ptr = ptr->link)
		printf("%8.2f %8d\n", ptr->coef, ptr->expon);
}

polyPointer cpadd(polyPointer a, polyPointer b)
//두 다항식을 더하는 함수
{
	polyPointer c;
	int sum, done = 0;

	a = a->link;
	b = b->link; //더미노드 건너띄기

	//내용이 빈 원형 연결 리스트 c을 만들고 시작
	c = getNode();
	c->coef = -1; c->expon = -1; c->link = c;

	do {
		switch (COMPARE(a->expon, b->expon))
		{
		case -1:
			attach(b->coef, b->expon, c);
			b = b->link;
			break;
		case 0:
			if (a->expon == -1) done = 1;
			else {
				sum = a->coef + b->coef;
				if (sum)
					attach(sum, a->expon, c);
				a = a->link;
				b = b->link;
			}
			break;
		case 1:
			attach(a->coef, a->expon, c);
			a = a->link;
			break;
		}
	} while (!done);
	return c;
}

polyPointer single_mul(struct poly Ai, polyPointer B)
//A의 항 하나와 B의 다항식을 곱하는 함수
{
	float coef;
	int expon;
	polyPointer Mi;
	B = B->link; //더미노드 건너띄기

	Mi = getNode();
	Mi->expon = -1; Mi->expon = -1; Mi->link = Mi;

	while (B->expon != -1) {
		attach(Ai.coef * B->coef, Ai.expon + B->expon, Mi);
		B = B->link;
	}

	return Mi;
}

polyPointer cpmul(polyPointer A, polyPointer B)
//A 다항식과 B 다항식을 곱하는 함수
{
	polyPointer X, D, tempD;
	A = A->link; //더미노드 건너띄기

	D = getNode();
	D->coef = -1; D->expon = -1; D->link = D; //D 다항식을 더미노드만 있는 원형 리스트로 생성

	int i = 1;
	while (A->expon != -1)
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
	A = NULL, B = NULL, C = NULL, D = NULL;
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