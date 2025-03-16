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
polyPointer A, B, C;

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

int main(void)
{
	A = NULL, B = NULL, C = NULL;
	avail = NULL;

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
	printf("다항식 덧셈 결과 : D(x)");
	C = cpadd(A, B);
	print_polynomial(C);

	return 0;
}