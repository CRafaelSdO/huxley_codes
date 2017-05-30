#include <stdio.h>

int main(int argc, char *argv[])
{
	float n, m;

	scanf("%f%f", &n, &m);

	n *= n * 3.14;
	m *= m * 3.14;

	printf("%s\n", (n == m)? "Iguais" : (n > m)? "Primeiro circulo" : "Segundo circulo");
	
	return 0;
}