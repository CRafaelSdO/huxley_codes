#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _list list_t;

list_t *new_list();

void add(int, list_t *);

void print_list(list_t *);

void destroy_list(list_t *);

typedef struct _hash_table hash_t;

hash_t *new_hash_table(int);

void put(int, hash_t *);

void print_hash_table(hash_t *);

void destroy_hash_table(hash_t *);

int main(int argc, char *argv[]) {
	int n, m, c, k, i, j;

	hash_t *ht;

	scanf("%d", &n);

	for (i = 0; i < n; i++) {
		scanf("%d%d", &m, &c);

		ht = new_hash_table(m);

		for (j = 0; j < c; j++) {
			scanf("%d", &k);

			put(k, ht);
		}

		print_hash_table(ht);

		destroy_hash_table(ht);
	}
	
	return 0;
}

typedef struct _node node_t;

struct _node{
	int item;
	node_t *next;
};

node_t *new_node(int item)
{
	node_t *new = (node_t *) calloc(1, sizeof(node_t));

	new->item = item;
	new->next = NULL;

	return new;
}

struct _list {
	int size;
	node_t *head;
	node_t *tail;
};

list_t *new_list()
{
	list_t *new = (list_t *) calloc(1, sizeof(list_t));

	new->size = 0;
	new->head = NULL;
	new->tail = NULL;

	return new;
}

bool is_empty(list_t *list)
{
	return list->size == 0;
}

void add(int item, list_t *list)
{
	node_t *to_add = new_node(item);

	if (is_empty(list)) {
		list->head = to_add;
		list->tail = to_add;
	} else {
		list->tail->next = to_add;
		list->tail = to_add;
	}

	list->size++;
}

void pop(list_t *list)
{
	if (!is_empty(list)) {
		node_t *tmp = list->head;

		list->head = list->head->next;

		free(tmp);

		list->size--;
	}
}

void print_list(list_t *list)
{
	node_t *tmp = list->head;

	while (tmp != NULL) {
		printf("%d -> ", tmp->item);

		tmp = tmp->next;
	}

	printf("\\\n");
}

void destroy_list(list_t *list)
{
	while (!is_empty(list)) {
		pop(list);
	}

	free(list);
}

struct _hash_table {
	int cap;
	list_t **table;
};

hash_t *new_hash_table(int cap)
{
	int i;

	hash_t *new = (hash_t *) calloc(1, sizeof(hash_t));

	new->cap = cap;
	new->table = (list_t **) calloc(cap, sizeof(list_t *));

	for (i = 0; i < cap; i++) {
		new->table[i] = new_list();
	}

	return new;
}

void put(int key, hash_t *hash_table)
{
	if (hash_table != NULL) {
		int h = key % hash_table->cap;

		add(key, hash_table->table[h]);
	}
}

void print_hash_table(hash_t *hash_table)
{
	if (hash_table != NULL) {
		int i;

		for (i = 0; i < hash_table->cap; i++) {
			printf("%d -> ", i);
			print_list(hash_table->table[i]);
		}

		printf("\n");
	}
}

void destroy_hash_table(hash_t *hash_table)
{
	if (hash_table != NULL) {
		int i;
		
		for (i = 0; i < hash_table->cap; i++) {
			destroy_list(hash_table->table[i]);
		}

		free(hash_table->table);
		free(hash_table);
	}
}