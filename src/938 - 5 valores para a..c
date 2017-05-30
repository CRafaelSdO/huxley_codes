#include <stdio.h>

int main(int argc, char *argv[])
{
	int count = 0, i;
	float n;

	for (i = 0; i < 5; i++) {
		printf("Digite um valor:\n");
		scanf("%f", &n);
		count = (n < 0)? count + 1 : count;
	}

	printf("Foram digitados %d numeros negativos\n", count);
	
	return 0;
}