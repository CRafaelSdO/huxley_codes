#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//Linked List ------------------------------------------------------------------
typedef struct _linked_list list_t;

list_t *newList();

void destroyList(list_t *);

void add(char, list_t *);

void printList(list_t *);

//Stack Functions --------------------------------------------------------------
typedef struct _stack stack_t;

stack_t *newStack();

bool isSEmpty(stack_t *);

void destroyStack(stack_t *);

void push(list_t *, stack_t *);

list_t *pop(stack_t *);

//Main Function ----------------------------------------------------------------
int main(int argc, char *argv[])
{
	char *cmd = (char *) calloc(5, sizeof(char));

	stack_t *stack = newStack();
	list_t *list;

	while (scanf("%s", cmd) != EOF) {
		getchar();
		if (!strcmp(cmd, "PUSH")) {
			char aux;

			list = newList();

			scanf("%c", &aux);

			while (aux != '\n') {
				add(aux, list);
				scanf("%c", &aux);
			}

			push(list, stack);
		} else if (!strcmp(cmd, "POP")) {
			if (isSEmpty(stack)) {
				printf("EMPTY STACK\n");
			} else {
				list = pop(stack);

				printList(list);
				destroyList(list);
			}
		}
	}

	return 0;
}

//List Node --------------------------------------------------------------------
typedef struct _lNode lNode_t;

struct _lNode {
	char item;
	lNode_t *next;
};

lNode_t *newLNode(char item)
{
	lNode_t *new = (lNode_t *) calloc(1, sizeof(lNode_t));

	new->item = item;
	new->next = NULL;

	return new;
}

//List -------------------------------------------------------------------------
struct _linked_list {
	int size;
	lNode_t *head;
	lNode_t *tail;
};

list_t *newList()
{
	list_t *new = (list_t *) calloc(1, sizeof(list_t));

	new->size = 0;
	new->head = NULL;
	new->tail = NULL;

	return new;
}

bool isLEmpty(list_t *list)
{
	return list->size == 0;
}

void destroyList(list_t *list)
{
	lNode_t *tmp;

	while (!isLEmpty(list)) {
		tmp = list->head;
		list->head = list->head->next;
		list->size--;
		free(tmp);
	}
}

void add(char item, list_t *list)
{
	lNode_t *toAdd = newLNode(item);

	if (isLEmpty(list)) {
		list->head = toAdd;
		list->tail = toAdd;
	} else {
		list->tail->next = toAdd;
		list->tail = toAdd;
	}

	list->size++;
}

void printList(list_t *list)
{
	lNode_t *tmp = list->head;

	while (tmp != NULL) {
		printf("%c", tmp->item);
		tmp = tmp->next;
	}

	printf("\n");
}

//Stack Node -------------------------------------------------------------------
typedef struct _sNode sNode_t;

struct _sNode {
	list_t *item;
	sNode_t *bot;
};

sNode_t *newSNode(list_t *item)
{
	sNode_t *new = (sNode_t *) calloc(1, sizeof(sNode_t));

	new->item = item;
	new->bot = NULL;

	return new;
}

void destroySNode(sNode_t *toDestroy)
{
	destroyList(toDestroy->item);
	free(toDestroy);
}

//Stack ------------------------------------------------------------------------
struct _stack {
	int size;
	sNode_t *top;
};


stack_t *newStack()
{
	stack_t *new = (stack_t *) calloc(1, sizeof(stack_t));

	new->size = 0;
	new->top = NULL;

	return new;
}

bool isSEmpty(stack_t *stack)
{
	return stack->size == 0;
}

void destroyStack(stack_t *stack)
{
	sNode_t *tmp;

	while (!isSEmpty(stack)) {
		pop(stack);
	}
}

void push(list_t *item, stack_t *stack)
{
	sNode_t *toPush = newSNode(item);

	toPush->bot = stack->top;
	stack->top = toPush;
	stack->size++;
}

list_t *pop(stack_t *stack)
{
	sNode_t *tmpN = stack->top;
	list_t *tmpL = tmpN->item;

	stack->top = stack->top->bot;
	stack->size--;

	free(tmpN);

	return tmpL;
}