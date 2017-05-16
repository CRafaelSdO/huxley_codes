#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

#define MAX 1000000

typedef struct _bt bt_t;

bt_t *new_bt();

void form_bt(bt_t *, char *, int);

bool dfs_bt(bt_t *, int, int *);

int main(int argc, char *argv[]) {
	int n;
	
	int d = -1;
	
	char *str = (char *) calloc(MAX, sizeof(char));
	bt_t *bt = new_bt();

	scanf("%[^\n]s", str);
	form_bt(bt, str, 0);
	scanf("%d", &n);

	if (dfs_bt(bt, n, &d)) {
		printf("ESTA NA ARVORE\n");
	} else {
		printf("NAO ESTA NA ARVORE\n");
	}

	printf("%d\n", d);
	
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

bool dfs_node(node_t *node, int item, int *d, int cd)
{
	if (node != NULL) {
		if (node->item == item) {
			(*d) = cd;
			return true;
		} else {
			if (!dfs_node(node->left, item, d, cd + 1)) {
				return dfs_node(node->right, item, d, cd + 1);
			} else {
				return true;
			}
		}
	} else {
		return false;
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

bool dfs_bt(bt_t *bt, int item, int *d)
{
	return dfs_node(bt->root, item, d, 0);
}