#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//Node Functions
typedef struct _node node_t;

node_t *newNode();

//Stack Functions
typedef struct _stack stack_t;

stack_t *newStack();

bool isEmpty(stack_t *);

int size(stack_t *);

void push(node_t *, stack_t *);

node_t *pop(stack_t *);

void destroy_stack(stack_t *);

//Main Function
int main(int argc, char *argv[])
{
	char *cmd = (char *) calloc(9, sizeof(char));

	node_t *current = NULL;
	stack_t *back = newStack();
	stack_t *forward = newStack();

	while (scanf("%s", cmd) != EOF) {
                if (!strcmp(cmd, "ENTER")) {
			if (current == NULL) {
				current = newNode();
			} else {
				push(current, back);

				current = newNode();
			}

			destroy_stack(forward);
		} else if (!strcmp(cmd, "BACK")) {
			if (!isEmpty(back)) {
				push(current, forward);

				current = pop(back);
			}
		} else if (!strcmp(cmd, "FORWARD")) {
			if (!isEmpty(forward)) {
				push(current, back);

				current = pop(forward);
			}
		}
	}

	printf("BACK: %d\nFORWARD: %d\n", size(back), size(forward));

	destroy_stack(back);
	destroy_stack(forward);
	
	return 0;
}

//Node
struct _node {
	node_t *bot;
};

node_t *newNode()
{
	node_t *new = (node_t *) calloc(1, sizeof(node_t));

	new->bot = NULL;

	return new;
}

//Stack
struct _stack {
	int size;
	node_t *top;
};

stack_t *newStack()
{
	stack_t *new =  (stack_t *) calloc(1, sizeof(stack_t));

	new->size = 0;
	new->top = NULL;

	return new;
}

bool isEmpty(stack_t *stack)
{
	return stack->size == 0;
}

int size(stack_t *stack)
{
	return stack->size;
}

void push(node_t *node, stack_t *stack)
{
	if (stack != NULL && node != NULL) {
		node->bot = stack->top;
		stack->top = node;
		stack->size++;
	}
}

node_t *pop(stack_t *stack)
{
	if (stack != NULL) {
		node_t *tmp = stack->top;
		stack->top = stack->top->bot;
		stack->size--;
		tmp->bot = NULL;

		return tmp;
	} else {
		return NULL;
	}
}

void destroy_stack(stack_t *stack)
{
	while (!isEmpty(stack)) {
		pop(stack);
	}
}