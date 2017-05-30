#include <stdio.h>

int main(int argc, char *argv[])
{
	int n;

	while (scanf("%d", &n), n != 0) {
		printf("%d - %d\n", ((n >> 1) + 1) * ((n >> 1) + 1), (n >> 1) * (n >> 1));
	}
	
	return 0;
}