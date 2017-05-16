#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _bt bt_t;

bt_t *new_bt();

void add_bt(int, bt_t *);

void print_bt(bt_t *);

int main(int argc, char *argv[]) {
	int n;

	bt_t *bt = new_bt();

	printf("----");

	while (scanf("%d", &n) != EOF) {
		add_bt(n, bt);
		print_bt(bt);
	}
	
	return 0;
}

typedef struct _node node_t;

struct _node {
	int item;
	node_t *left;
	node_t *right;
};

node_t *new_node(int item)
{
	node_t *new = (node_t *) calloc(1, sizeof(node_t));

	new->item = item;
	new->left = NULL;
	new->right = NULL;

	return new;
}

void add_node(node_t *to_add, node_t **source)
{
	if ((*source) == NULL) {
		(*source) = to_add;
	} else if (to_add->item < (*source)->item) {
		add_node(to_add, &(*source)->left);
	} else {
		add_node(to_add, &(*source)->right);
	}
}

void print_node(node_t *node)
{
	if (node == NULL) {
		printf(" () ");
	} else {
		printf(" ( %d ", node->item);
		print_node(node->left);
		print_node(node->right);
		printf(") ");
	}
}

struct _bt {
	node_t *root;
};

bt_t *new_bt()
{
	bt_t *new = (bt_t *) calloc(1, sizeof(bt_t));

	new->root = NULL;

	return new;
}

void add_bt(int item, bt_t *bt)
{
	printf("\nAdicionando %d\n", item);
	node_t *to_add = new_node(item);

	add_node(to_add, &bt->root);
}

void print_bt(bt_t *bt)
{
	printf("  ");
	print_node(bt->root);
	printf("\n----");
}