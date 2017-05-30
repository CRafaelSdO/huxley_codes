#include <stdio.h>

int main(int argc, char *argv[])
{
	float pH;

	scanf("%f", &pH);
	printf("%s\n", (pH == 7)? "Neutra" : (pH > 7)? "Basica" : "Acida");
	
	return 0;
}