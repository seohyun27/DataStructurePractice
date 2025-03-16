#include <stdio.h>
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100

//내부적으로는 숫자로 사용하게 됨
typedef enum {lparen, rparen, plus, minus, times,
		divide, mod, eos, operand} precedence;

int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 }; //스택 밖 연산자 우선 순위
int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 }; //스택 안 연산자 우선 순위

int stack[MAX_STACK_SIZE], top = -1;
char expr[MAX_EXPR_SIZE];
char new_expr[MAX_EXPR_SIZE];

//infix와 fostfix 스택 2개
//각 스택마다 push, pop 함수 따로 구현

void push(int item)
{
	if (top >= MAX_STACK_SIZE - 1)
		printf("The stack is full.\n");
	else
		stack[++top] = item;
}

int pop()
{
	if (top == -1)
	{
		printf("The stack is empty.\n\n");
		return -1;
	}
	return stack[top--];
}

void print_stack()
{
	printf("    index : item\n");
	for (int i = 0; i <= top;i++)
		printf("\t%d : %d\n", i, stack[i]);
	printf("\n");
}

void strcpy(char* dest, const char* src) 
{ //문자열 복사 함수
	int i = 0;
	while (src[i] != '\0') { //복사하려는 문자열에 null을 만날 때까지 반복
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0'; // 문자열 끝에 null 문자 추가
}

char printToken(precedence token)
//token을 출력하기 위한 printToken 함수
{
	switch (token) {
	case plus: return '+';
	case minus: return '-';
	case times: return '*';
	case divide: return '/';
	case mod: return '%';
	case lparen: return '(';
	case rparen: return ')';
	}
}

void printString(char dest[]) 
{
	int i = 0;

	while (dest[i] != '\0') { //null를 만날 때까지
		printf("%c", dest[i]);
		i++;
	}
}

precedence get_token(char* symbol, int* n) //expr인수도 받아서 작동하도록 수정
//expr[*(n)] 값을 검사하여 해당 token을 반환
{
	//expr이라는 문자 배열의 expr[*(n)]값을 *symbol에 담고 n += 1;을 해준다
	*symbol = expr[(*n)++];
	switch (*symbol)
	{
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	case '%': return mod;
	case '\0': return eos;
	default: return operand; //검사 결과 없다면 숫자라는 사실을 반환
	}
}

//void post_print(char symbol, expr, index) 함수 만들어서 필요한 위치마다 불러오기
//post_print(')', post_expr, index); 호출
//post_print(symbol, post_expr, index); 호출

int eval(char* expr) //후위 연산 계산 함수
{
	//expr 배열에 마지막은 '\0' 값이 들어가 있음
	precedence token;
	char symbol;
	int op1, op2;
	int n = 0; //문자열 expr의 현재 위치
	top = -1;

	printf("\nEval of Postfix :\n");
	printf("Token | Stack\t\t       | Top\n");
	token = get_token(&symbol, &n); //숫자인지 연산자인지 검사
	while (token != eos) { //배열의 마지막이 나올 때까지
		if (token == operand) //token이 숫자라면
			push(symbol - '0'); //숫자로 만들어 스택에 저장
		else { //연산자라면
			op2 = pop();
			op1 = pop();
			switch (token) { //후위 연산자에는 괄호가 없음
			case plus: push(op1 + op2); break;
			case minus: push(op1 - op2); break;
			case times: push(op1 * op2); break;
			case divide: push(op1 / op2); break;
			case mod: push(op1 % op2); break;
				
			}
		}
		//계산 과정 출력
		if (token == operand)
			printf("   %c  |", symbol);
		else
			printf("   %c  |", printToken(token));
		for (int i = 0; i <= top;i++)
			printf(" %d ", stack[i]);
		for (int i = 0; i < 7 - top;i++)
			printf("   ");
		printf("| %d", top);
		printf("\n");

		token = get_token(&symbol, &n); //while문의 다음 반복을 위해 token을 받아둔다
	}
	return pop(); //최종 결과를 리턴
}

char* postfix(char* expr, char* new_expr)
{
	//infix expr[] -> postfix new_expr[]
	
	char symbol;
	precedence token = 0;
	int n = 0; //문자열 expr의 현재 위치
	int new_n = 0; //문자열 new_expr의 현재 위치
	top = 0; //stack[0]에 eos를 담고 시작해야 함(top 증가)
	stack[0] = eos;
	printf("Infix : ");
	printString(expr);
	printf("\nInfix to Postfix : ");
	printf("\nToken | Stack\t\t       | Top   | Output\n");

	for (token = get_token(&symbol, &n);token != eos;token = get_token(&symbol, &n))
	//token이 null을 만날 때까지
	{
		if (token == operand) //token이 숫자라면
			new_expr[new_n++] = symbol;
		else if (token == rparen) { //token이 오른쪽 괄호라면
			while (stack[top] != lparen) //왼쪽 괄호 나올 때까지 pop
				new_expr[new_n++] = printToken(pop());
			pop(); //담아뒀던 왼쪽 괄호 버리기
		}
		else { //숫자도 괄호도 아니라면
			while (isp[stack[top]] >= icp[token]) //연산자 우선순위 비교
				new_expr[new_n++] = printToken(pop()); //더 낮은 우선순위가 나올 때까지 pop
			push(token);
		}
		//계산 과정 출력
		if (token != rparen)
		{
			if (token == operand)
				printf("   %c  |", symbol);
			else
				printf("   %c  |", printToken(token));
			for (int i = 1; i <= top;i++)
				printf(" %c ", printToken(stack[i]));
			for (int i = 0; i < 8 - top;i++)
				printf("   ");
			printf("| %d     | ", top);
			printString(new_expr);

			printf("\n");
		}
	}
	//for문이 끝났다면
	while (top > 0) { //stack에 남은 연산자 출력
		new_expr[new_n++] = printToken(pop());
	}
	//계산 과정 출력
	if (token != rparen)
	{
		if (token == operand)
			printf("   %c  |", symbol);
		else
			printf("   %c  |", printToken(token));
		for (int i = 1; i <= top;i++)
			printf(" %c ", printToken(stack[i]));
		for (int i = 0; i < 8 - top;i++)
			printf("   ");
		printf("| %d    | ", top);
		printString(new_expr);
		printf("\n");
	}

	new_expr[new_n] = '\0'; //식의 마지막에 null값 넣어주기

	return new_expr;
}

int main()
{
	strcpy(expr, "((((6/2)-3+(4*2))-5*3))");
	postfix(expr, new_expr);
	printf("Postfix : ");
	printString(new_expr);
	top = -1; //스택 초기화
	//getToken이 expr에 대해서 작동 -> new_expr의 배열 expr로 옮겨주기
	strcpy(expr, new_expr);
	printf("Eval : %d", eval(expr));
	printf("\n");

	return 0;
}