#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//Stack Functions --------------------------------------------------------------
typedef struct _stack stack_t;

stack_t *newStack();

bool isEmpty(stack_t *);

int size(stack_t *);

char peak(stack_t *);

void push(char, stack_t *);

void pop(stack_t *);

void destroy_stack(stack_t *);

//Main Function ----------------------------------------------------------------
int main(int argc, char *argv[])
{
	int n, i, j;
	bool balanced;

	char str[256];

	stack_t *stack = newStack();

	scanf("%d\n", &n);

	for (i = 0; i < n; i++) {
		balanced = true;

		fgets(str, 256, stdin);

		for (j = 0; j < strlen(str); j++) {
			switch (str[j]) {
				case '(': case '[':
					push(str[j], stack);
					break;
				case ')':
					if (!isEmpty(stack)) {
						if (peak(stack) == '(') {
							pop(stack);
						} else {
							balanced = false;
						}
					} else {
						balanced = false;
					}
					break;
				case ']':
					if (!isEmpty(stack)) {
						if (peak(stack) == '[') {
							pop(stack);
						} else {
							balanced = false;
						}
					} else {
						balanced = false;
					}
					break;
			}
		}

		if ((balanced && !(size(stack) % 2)) || !strlen(str)) {
			printf("Yes\n");
		} else {
			printf("No\n");
		}

		destroy_stack(stack);
	}

	return 0;
}

//Node -------------------------------------------------------------------------
typedef struct _node node_t;

struct _node {
	char item;
	node_t *bot;
};

node_t *newNode(char item)
{
	node_t *new = (node_t *) calloc(1, sizeof(node_t));

	new->item = item;
	new->bot = NULL;

	return new;
}

//Stack ------------------------------------------------------------------------
struct _stack {
	int size;
	node_t *top;
};

stack_t *newStack()
{
	stack_t *new = (stack_t *) calloc(1, sizeof(stack_t));

	new->size = 0;
	new->top = NULL;

	return new;
}

bool isEmpty(stack_t *stack)
{
	if (stack != NULL) {
		return stack->size == 0;
	} else {
		return true;
	}
}

int size(stack_t *stack)
{
	if (stack != NULL) {
		return stack->size;
	} else {
		return 0;
	}
}

char peak(stack_t *stack)
{
	if (stack != NULL) {
		return stack->top->item;
	} else {
		return '\0';
	}
}

void push(char item, stack_t *stack)
{
	if (stack != NULL) {
		node_t *toPush = newNode(item);

		toPush->bot = stack->top;
		stack->top = toPush;
		stack->size++;
	}
}

void pop(stack_t *stack)
{
	if (stack != NULL) {
		node_t *tmp = stack->top;

		stack->top = stack->top->bot;
		stack->size--;

		free(tmp);
	}
}

void destroy_stack(stack_t *stack)
{
	while (!isEmpty(stack)) {
		pop(stack);
	}
}