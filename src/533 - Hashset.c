#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX(x, y) ((x > y)? x : y);

typedef struct _hash hash_t;

hash_t *new_hash(int);

void rehash(hash_t *);

bool need_rehash(hash_t *);

bool put(int, hash_t *, int *);

bool rem(int, hash_t *, int *);

bool has(int, hash_t *, int *);

void prt(hash_t *, int);

void destroy_hash(hash_t *);

int main(int argc, char *argv[]) {
	int i = 0;

	int r;
	int c, key;
	char cmd[4];

	hash_t *ht = new_hash(7);

	while (scanf("%s", cmd) != EOF) {
		if (!strcmp(cmd, "PRT")) {
			prt(ht, i++);
		} else {
			scanf("%d", &key);

			if (!strcmp(cmd, "ADD")) {
				r = (put(key, ht, &c))? 1 : 0;
			}

			if (!strcmp(cmd, "DEL")) {
				r = (rem(key, ht, &c))? 1 : 0;
			}

			if (!strcmp(cmd, "HAS")) {
				r = (has(key, ht, &c))? 1 : 0;
			}

			printf("%d %d %d\n", i++, r, c);
		}
	}

	destroy_hash(ht);
	
	return 0;
}

typedef struct _node node_t;

struct _node {
	int item;
	node_t *next;
	node_t *prev;
};

node_t *new_node(int item)
{
	node_t *new = (node_t *) calloc(1, sizeof(node_t));

	new->item = item;
	new->next = NULL;
	new->prev = NULL;

	return new;
}

typedef struct _list list_t;

struct _list {
	int size;
	node_t *head;
};

list_t *new_list()
{
	list_t *new = (list_t *) calloc(1, sizeof(list_t));

	new->size = 0;
	new->head = NULL;

	return new;
}

void destroy_list(list_t *list)
{
	if (list != NULL) {
		node_t *tmp = list->head;

		while (tmp != NULL) {
			list->head = tmp->next;

			free(tmp);

			tmp = list->head;
		}

		free(list);
	}
}

bool list_is_empty(list_t *list)
{
	if (list != NULL) {
		return list->size == 0;
	} else {
		return true;
	}
}

int list_size(list_t *list)
{
	if (list != NULL) {
		return list->size;
	} else {
		return 0;
	}
}

bool list_has(int item , list_t *list, int *c)
{
	if (list != NULL) {
		node_t *tmp = list->head;

		while (tmp != NULL) {
			(*c)++;

			if (tmp->item == item) {
				return true;
			}

			tmp = tmp->next;
		}

		return false;
	} else {
		return false;
	}
}

bool add_to_list(int item, list_t *list, int *c)
{
	if (list != NULL) {
		node_t *to_add = new_node(item);

		if (list_is_empty(list)) {
			list->head = to_add;
		} else {
			if (!list_has(item, list, c)) {
				to_add->next = list->head;
				list->head->prev = to_add;
				list->head = to_add;
			} else {
				free(to_add);

				return false;
			}
		}

		list->size++;

		return true;
	} else {
		return false;
	}
}

bool del_from_list(int item, list_t *list, int *c)
{
	if (list != NULL) {
		node_t *tmp = list->head;

		while (tmp != NULL) {
			(*c)++;

			if (tmp->item == item) {
				if (tmp->prev != NULL) {
					tmp->prev->next = tmp->next;
				} else {
					list->head = tmp->next;
				}

				if (tmp->next != NULL) {
					tmp->next->prev = tmp->prev;
				}

				free(tmp);

				list->size--;

				return true;
			}

			tmp = tmp->next;
		}

		return false;
	} else {
		return false;
	}
}

struct _hash{
	int cap;
	int size;
	list_t **table;
};

hash_t *new_hash(int cap)
{
	int i;

	hash_t *new = (hash_t *) calloc(1, sizeof(hash_t));

	new->cap = cap;
	new->size = 0;
	new->table = (list_t **) calloc(cap, sizeof(list_t *));

	for (i = 0; i < cap; i++) {
		new->table[i] = NULL;
	}

	return new;
}

void rehash(hash_t *hash)
{
	if (hash != NULL) {
		int i;
		int tmp_int;

		hash_t *tmp_hash = new_hash(2 * hash->cap - 1);

		for (i = 0; i < hash->cap; i++) {
			if (hash->table[i] != NULL) {
				node_t *tmp_node = hash->table[i]->head;

				while (tmp_node != NULL) {
					put(tmp_node->item, tmp_hash, &tmp_int);
					tmp_node = tmp_node->next;
				}
			}
		}

		for (i = 0; i < hash->cap; i++) {
			if (hash->table[i] != NULL) {
				destroy_list(hash->table[i]);
				hash->table[i] = NULL;
			}
		}

		free(hash->table);

		hash->cap = tmp_hash->cap;
		hash->table = tmp_hash->table;

		free(tmp_hash);
	}
}

bool need_rehash(hash_t *hash)
{
	if (hash != NULL) {
		return (float) hash->size / hash->cap >= 0.75;
	} else {
		return false;
	}
}

bool put(int key, hash_t *hash, int *c)
{
	if (hash != NULL) {
		int h = key % hash->cap;

		(*c) = 0;

		if (hash->table[h] == NULL) {
			hash->table[h] = new_list();
		}

		if (add_to_list(key, hash->table[h], c)) {
			hash->size++;

			if (need_rehash(hash)) {
				rehash(hash);
			}

			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool rem(int key, hash_t *hash, int *c)
{
	if (hash != NULL) {
		int h = key % hash->cap;

		(*c) = 0;

		if (hash->table[h] == NULL) {
			return false;
		}

		if (del_from_list(key, hash->table[h], c)) {
			if (list_is_empty(hash->table[h])) {
				destroy_list(hash->table[h]);
				hash->table[h] = NULL;
			}

			hash->size--;

			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool has(int key, hash_t *hash, int *c)
{
	if (hash != NULL) {
		int h = key % hash->cap;

		(*c) = 0;

		if (hash->table[h] == NULL) {
			return false;
		}

		return list_has(key, hash->table[h], c);
	} else {
		return false;
	}
}

void prt(hash_t *hash, int i)
{
	if (hash != NULL) {
		int idx;

		int l = 0;
		
		int m = hash->cap;
		int n = hash->size;

		for (idx = 0; idx < hash->cap; idx++) {
			if (hash->table[idx] != NULL) {
				l = MAX(l, list_size(hash->table[idx]));
			}
		}

		printf("%d %d %d %d\n", i, m, n, l);
	}
}

void destroy_hash(hash_t *hash)
{
	if (hash != NULL) {
		int i;

		for (i = 0; i < hash->cap; i++) {
			if (hash->table[i] != NULL) {
				destroy_list(hash->table[i]);
			}
		}

		free(hash);
	}
}