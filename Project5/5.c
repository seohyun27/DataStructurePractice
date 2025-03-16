#include <stdio.h>
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100

//���������δ� ���ڷ� ����ϰ� ��
typedef enum {lparen, rparen, plus, minus, times,
		divide, mod, eos, operand} precedence;

int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 }; //���� �� ������ �켱 ����
int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 }; //���� �� ������ �켱 ����

int stack[MAX_STACK_SIZE], top = -1;
char expr[MAX_EXPR_SIZE];
char new_expr[MAX_EXPR_SIZE];

//infix�� fostfix ���� 2��
//�� ���ø��� push, pop �Լ� ���� ����

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
{ //���ڿ� ���� �Լ�
	int i = 0;
	while (src[i] != '\0') { //�����Ϸ��� ���ڿ��� null�� ���� ������ �ݺ�
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0'; // ���ڿ� ���� null ���� �߰�
}

char printToken(precedence token)
//token�� ����ϱ� ���� printToken �Լ�
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

	while (dest[i] != '\0') { //null�� ���� ������
		printf("%c", dest[i]);
		i++;
	}
}

precedence get_token(char* symbol, int* n) //expr�μ��� �޾Ƽ� �۵��ϵ��� ����
//expr[*(n)] ���� �˻��Ͽ� �ش� token�� ��ȯ
{
	//expr�̶�� ���� �迭�� expr[*(n)]���� *symbol�� ��� n += 1;�� ���ش�
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
	default: return operand; //�˻� ��� ���ٸ� ���ڶ�� ����� ��ȯ
	}
}

//void post_print(char symbol, expr, index) �Լ� ���� �ʿ��� ��ġ���� �ҷ�����
//post_print(')', post_expr, index); ȣ��
//post_print(symbol, post_expr, index); ȣ��

int eval(char* expr) //���� ���� ��� �Լ�
{
	//expr �迭�� �������� '\0' ���� �� ����
	precedence token;
	char symbol;
	int op1, op2;
	int n = 0; //���ڿ� expr�� ���� ��ġ
	top = -1;

	printf("\nEval of Postfix :\n");
	printf("Token | Stack\t\t       | Top\n");
	token = get_token(&symbol, &n); //�������� ���������� �˻�
	while (token != eos) { //�迭�� �������� ���� ������
		if (token == operand) //token�� ���ڶ��
			push(symbol - '0'); //���ڷ� ����� ���ÿ� ����
		else { //�����ڶ��
			op2 = pop();
			op1 = pop();
			switch (token) { //���� �����ڿ��� ��ȣ�� ����
			case plus: push(op1 + op2); break;
			case minus: push(op1 - op2); break;
			case times: push(op1 * op2); break;
			case divide: push(op1 / op2); break;
			case mod: push(op1 % op2); break;
				
			}
		}
		//��� ���� ���
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

		token = get_token(&symbol, &n); //while���� ���� �ݺ��� ���� token�� �޾Ƶд�
	}
	return pop(); //���� ����� ����
}

char* postfix(char* expr, char* new_expr)
{
	//infix expr[] -> postfix new_expr[]
	
	char symbol;
	precedence token = 0;
	int n = 0; //���ڿ� expr�� ���� ��ġ
	int new_n = 0; //���ڿ� new_expr�� ���� ��ġ
	top = 0; //stack[0]�� eos�� ��� �����ؾ� ��(top ����)
	stack[0] = eos;
	printf("Infix : ");
	printString(expr);
	printf("\nInfix to Postfix : ");
	printf("\nToken | Stack\t\t       | Top   | Output\n");

	for (token = get_token(&symbol, &n);token != eos;token = get_token(&symbol, &n))
	//token�� null�� ���� ������
	{
		if (token == operand) //token�� ���ڶ��
			new_expr[new_n++] = symbol;
		else if (token == rparen) { //token�� ������ ��ȣ���
			while (stack[top] != lparen) //���� ��ȣ ���� ������ pop
				new_expr[new_n++] = printToken(pop());
			pop(); //��Ƶ״� ���� ��ȣ ������
		}
		else { //���ڵ� ��ȣ�� �ƴ϶��
			while (isp[stack[top]] >= icp[token]) //������ �켱���� ��
				new_expr[new_n++] = printToken(pop()); //�� ���� �켱������ ���� ������ pop
			push(token);
		}
		//��� ���� ���
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
	//for���� �����ٸ�
	while (top > 0) { //stack�� ���� ������ ���
		new_expr[new_n++] = printToken(pop());
	}
	//��� ���� ���
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

	new_expr[new_n] = '\0'; //���� �������� null�� �־��ֱ�

	return new_expr;
}

int main()
{
	strcpy(expr, "((((6/2)-3+(4*2))-5*3))");
	postfix(expr, new_expr);
	printf("Postfix : ");
	printString(new_expr);
	top = -1; //���� �ʱ�ȭ
	//getToken�� expr�� ���ؼ� �۵� -> new_expr�� �迭 expr�� �Ű��ֱ�
	strcpy(expr, new_expr);
	printf("Eval : %d", eval(expr));
	printf("\n");

	return 0;
}