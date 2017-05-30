#include <stdio.h>

int main(int argc, int *argv[])
{
	int n, m;

	scanf("%d%d", &n, &m);
	printf("%d\n", ((n > m)? n : m));
	
	return 0;
}