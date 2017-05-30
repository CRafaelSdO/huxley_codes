#include <stdio.h>

int main(int argc, char *argv[])
{
	int count = 0, i;
	float n[3], m;

	scanf("%f%f%f", &n[0], &n[1], &n[2]);

	m = (n[0] + n[1] + n[2]) / 3;

	for (i = 0; i < 3; i++) {
		if (n[i] > m) {
			count++;
		}
	}

	printf("%d\n", count);
	
	return 0;
}