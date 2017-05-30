#include <stdio.h>

int main(int argc, char *argv[])
{
	int n[2];

	scanf("%d%d", &n[0], &n[1]);

	if (n[0] > n[1]) {
		int aux = n[0];
		n[0] = n[1];
		n[1] = aux;
	}

	printf("%d %d", n[0], n[1]);
	
	return 0;
}