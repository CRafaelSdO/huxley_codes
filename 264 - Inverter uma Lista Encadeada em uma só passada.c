#include <stdio.h>
#include <stdlib.h>

typedef struct _node node_t;

node_t *newList();

void destroyNode(node_t *);

void printList(node_t *);

node_t *add(node_t *, int);

node_t *reverse(node_t *, node_t *);

int main()
{
	int i;
	node_t *listhead = newList();

	while (scanf("%d", &i) != EOF)
	{
		listhead = add(listhead, i);
	}

	listhead = reverse(NULL, listhead);

	printList(listhead);

	destroyNode(listhead);
}

struct _node {
	int item;
	node_t *next;
};

node_t *newList()
{
	return NULL;
}

void destroyNode(node_t *node)
{
	if (node != NULL) {
		destroyNode(node->next);
		free(node);
	}
}

void printList(node_t *head)
{
	if (head != NULL) {
		printList(head->next);
		printf("%d ", head->item);
	}
}
node_t *add(node_t *head, int item)
{
	node_t *new = (node_t *) malloc(sizeof(node_t));

	new->item = item;
	new->next = head;

	return new;
}

node_t *reverse(node_t *prev, node_t *current)
{
	if (current != NULL) {
		node_t *next = current->next;
		current->next = prev;
		return reverse(current, next);
	} else {
		return prev;
	}
}