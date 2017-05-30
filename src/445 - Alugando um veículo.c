#include <stdio.h>

int main(int argc, char *argv[])
{
	int d, km;

	scanf("%d%d", &d, &km);
	printf("%.2f\n", (float) (d * 90) + ((km > d * 100)? (km - d * 100) * 12 : 0));
	
	return 0;
}