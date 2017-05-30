#include <stdio.h>

int main(int argc, char *argv[])
{
	int n;

	scanf("%d", &n);
	printf("%s\n", (n % 5 == 0)? "Eh multiplo de 5" : "Nao eh multiplo de 5");
	
	return 0;
}