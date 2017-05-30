#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 1000000

typedef struct _bt bt_t;

bt_t *new_bt();

void form_bt(bt_t *, char *, int);

bool is_binary_search_tree(bt_t *);

int main(int argc, char *argv[])
{
	char *str = (char *) calloc(MAX, sizeof(char));
	bt_t *bt = new_bt();

	scanf("%[^\n]s", str);
	form_bt(bt, str, 0);

	if (is_binary_search_tree(bt)) {
		printf("VERDADEIRO\n");
	} else {
		printf("FALSO\n");
	}
	
	return 0;
}

typedef struct _node node_t;

struct _node {
	int item;
	node_t *left;
	node_t *right;
};

node_t *new_node(char *str, int *i)
{
	node_t *new;

	while (str[(*i)] == ' ' ) {
		(*i)++;
	}

	(*i)++;

	if (str[(*i)] == ')') {
		new = NULL;
		(*i)++;
	} else {
		char *n = (char *) calloc(8, sizeof(char));

		while (str[(*i)] != '(') {
			char tmp[] = {str[(*i)], '\0'};
			strcat(n, tmp);
			(*i)++;
		}

		new = (node_t *) calloc(1, sizeof(node_t));

		new->item = atoi(n);
		new->left = new_node(str, i);
		new->right = new_node(str, i);

		(*i)++;
	}

	return new;
}

bool is_binary_search_tree_node(node_t *node)
{
	if (node != NULL) {
		if (node->left == NULL && node->right == NULL) {
			return true;
		} else if (node->right == NULL) {
			if (node->item < node->left->item) {
				return false;
			} else {
				return true;
			}
		} else if (node->left == NULL) {
			if (node->item > node->right->item) {
				return false;
			} else {
				return true;
			}
		} else if (node->item < node->left->item ||
		node->item > node->right->item) {
			return false;
		} else {
			if (is_binary_search_tree_node(node->left)) {
				return is_binary_search_tree_node(node->right);
			} else {
				return false;
			}
		}
	} else {
		return true;
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

void form_bt(bt_t *bt, char *str, int i)
{
	bt->root = new_node(str, &i);
}

bool is_binary_search_tree(bt_t *bt)
{
	return is_binary_search_tree_node(bt->root);
}