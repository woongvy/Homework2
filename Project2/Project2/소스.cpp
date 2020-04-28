#include <stdio.h>
#include <string.h>

typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand } precedence;
char expr[1111];
static int isp[] = { 0,19,12,12,13,13,13,0 };
static int icp[] = { 20,19,12,12,13,13,13,0 };
#define MAX_SIZE 100
precedence stack[MAX_SIZE];
int top = -1;

precedence getToken(char *symbol, int *n)
{
	*symbol = expr[(*n)++];
	switch (*symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	case '%': return mod;
	case '\0': return eos;
	default: return operand;
	}
}

int isempty()
{
	if (top < 0)
		return 1;
	else
		return 0;
}

int isfull()
{
	if (top >= MAX_SIZE - 1)
		return 1;
	else
		return 0;
}


int push(precedence x)
{
	if (isfull())
	{
		return 0;
	}
	else
	{
		stack[++top] = x;
		return 1;
	}
}

precedence pop()
{
	if (isempty())
		return eos;
	else
	{
		precedence a = stack[top--];
		return a;
	}
}

void printToken(precedence token)
{
	switch (token)
	{
	case lparen:
		putc('(', stdout);
		break;
	case rparen:
		putc(')', stdout);
		break;
	case plus:
		putc('+', stdout);
		break;
	case minus:
		putc('-', stdout);
		break;
	case divide:
		putc('/', stdout);
		break;
	case times:
		putc('*', stdout);
		break;
	case mod:
		putc('%', stdout);
		break;
	case eos:
		putc('\0', stdout);
		break;
	default:
		break;
	}
}

void InfixToPostfix(void)
{
	precedence token;
	char symbol;
	int n = 0;
	top = -1;
	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n))
	{
		if (token == operand)
			printf("%c", symbol);
		else if (token == rparen)
		{
			while (stack[top] != lparen)
				printToken(pop());
			pop();
		}
		else
		{
			if (top == -1)
				push(token);
			else
			{
				while (isp[stack[top]] >= icp[token])
					printToken(pop());
				push(token);
			}
		}
	}
	while ((token = pop()) != eos)
		printToken(token);
	printf("\n");
}
int main()
{
	scanf("%s", expr);
	InfixToPostfix();
	return 0;
}