#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hash_function(char *, int);

int main(int argc, char *argv[]) {
	int n, l, hash, i, j;
	char *string = (char *) calloc(51, sizeof(char));

	scanf("%d", &n);

	for (i = 0; i < n; i++) {
		scanf("%d", &l);

		hash = 0;

		for (j = 0; j < l; j++) {
			scanf("%s", string);

			hash += hash_function(string, j);
		}

		printf("%d\n", hash);
	}
	
	return 0;
}

int hash_function(char *str, int index)
{
	int v = 0, i;

	for (i = 0; i < strlen(str);i++) {
		v += str[i] - 'A' + index + i;
	}

	return v;
}